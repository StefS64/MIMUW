#include <cassert>
#include <vector>
#include <random>
#include <iostream>
#include <climits>
#include <thread>
#include <chrono>
#include "prev.h"
#include <mutex>
#include "CLI11.hpp"

bool check_query(int i, const std::vector<int> &seq, std::mt19937 &gen, std::uniform_int_distribution<> &dist) {
    int lo = dist(gen);
    int hi = dist(gen);
    if (lo > hi) {
        std::swap(lo, hi);
    }
    assert(((size_t) i) < seq.size());
    int j = prevInRange(i, lo, hi);
    int expected = -1;
    for (int k = i; k >= 0; --k) {
        if (seq[k] >= lo && seq[k] <= hi) {
            expected = k;
            break;
        }
    }
    if (j != expected) {
        std::cout << "--------------------------------ERROR--------------------------------\n";
        std::cout << "STATE: ";
        for (auto& x : seq) {
            std::cout << x << " ";
        }
        std::cout << "\nWrong answer for query " << i << " " << lo << " " << hi << ": expected " << expected << ", got " << j << std::endl;
        return false;
    }
    return true;
}

std::mutex m;
size_t initial_size = 5;
size_t max_size = 10;
size_t current_size = 0;
int query_cnt = 10;
int initial_query_cnt = query_cnt;

void push(std::vector<int> &seq, int value) {
    seq.push_back(value);
    pushBack(value);
    std::unique_lock<std::mutex> lock(m);
    current_size = seq.size();
}

void spinnerThread() {
    const std::vector<std::string> spinners = {"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"};
    int i = 0;
    while (true) {
        {
            std::scoped_lock lock(m);
            std::cout << "\r[" << 100 * (initial_query_cnt - query_cnt) / initial_query_cnt << "%] " << spinners[i % spinners.size()] << "  " << query_cnt << " queries left, current size is " << current_size << " ";
            if(current_size >= max_size && query_cnt <= 0) {
                break;
            }
        }
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        i++;
    }
}

int main(int argc, char **argv) {
    std::mt19937 gen(time(nullptr));
    CLI::App app{"prevInRange tester"};
    app.add_option("-s,--size", initial_size, "Initial size of the sequence");
    app.add_option("-m,--max", max_size, "Maximum size of the sequence");
    app.add_option("-q,--query", query_cnt, "Number of queries");
    std::vector<int> seq;
    CLI11_PARSE(app, argc, argv);
    assert(initial_size <= max_size);
    assert(query_cnt > 0);
    initial_query_cnt = query_cnt;
    std::uniform_int_distribution<> dist(INT_MIN, INT_MAX);
    std::thread spinner(spinnerThread);
    for (size_t i = 0; i < initial_size; ++i) {
        seq.push_back(dist(gen));
        std::scoped_lock lock(m);
        current_size = seq.size();
    }
    init(seq);

    std::uniform_int_distribution<> binary_dist(0, 1);
    while(true) {
        int rnd = binary_dist(gen);

        {
            std::scoped_lock lock(m);
            if(query_cnt <= 0 && seq.size() >= max_size) {
                break;
            }
        }

        if (rnd) {
            {
                std::scoped_lock lock(m);
                if(seq.size() >= max_size) {
                    continue;
                }
            }
            int value = dist(gen);
            push(seq, value);
        } else { 
            {
                std::scoped_lock lock(m);
                if(query_cnt <= 0) {
                    continue;
                }
            }
            std::uniform_int_distribution<> i_dist(0, (int) seq.size() - 1);
            int i = i_dist(gen);
            if (check_query(i, seq, gen, dist)) {
                std::scoped_lock lock(m);
                query_cnt--;
            } else {
                return 1;
            }
        }
    }

    done();
    spinner.join();
    std::cout << "--------------------------------OK--------------------------------\n";
    return 0;
}
