// Tester do zadania Kolejki
// Kamil Szymczak

#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <cassert>
#include <algorithm>
#include <iterator>
#include <set>
#include "kol.h"

using namespace std;


// Odkomentuj #undef DEBUG aby pozbyć się wypisywania kroków.

#define DEBUG
#undef DEBUG

#ifdef DEBUG
#define debug(X) cout << X
#else
#define debug(...){}
#endif

mt19937 rng(1234);

int randint(int a, int b) {
    int r = rng() & ((1ull << 31) - 1);
    return a + r % (b - a + 1);
}


int main(int argc, char **argv) {
    
    if(argc > 1) {
        int seed = stoi(argv[1]);
        rng = mt19937(seed);
        debug("ziarno = " << seed << "\n" << flush);
    }
    
    
    // Zakresy można modyfikować aby generować duże/małe testy.
    int m = randint(2, 40);
    int q = randint(1, 5000);
    
    debug("m = " << m << "\n" << flush);
    
    vector<vector<int>>kolejki(m);
    
    map<int, interesant *>daj_interesanta;
    
    set<int>interesanci_w_okienkach;
    
    
    
    otwarcie_urzedu(m);
    
    debug("zaczynamy\n\n" << flush);

    
    while(q--) {
        int f = randint(1, 7);
        switch(f) {
            case 1: { // nowy_interesant()
              int k = randint(0, m - 1);
                debug("nowy_interesant na kolejce "<< k <<"\n" << flush);
                interesant *i = nowy_interesant(k);
                daj_interesanta[numerek(i)] = i;
                kolejki[k].push_back(numerek(i));
                
                interesanci_w_okienkach.insert(numerek(i));
                

                
            } break;
            case 2: { // numerek()
                //debug("dodaj numerek\n" << flush);
                if(daj_interesanta.empty()) {
                    q++;
                    continue;
                } else {
                    int ind = randint(0, (int)daj_interesanta.size() - 1);
                    auto it = daj_interesanta.begin();
                    advance(it, ind);
                    assert(it->first == numerek(it->second));
                    
                    debug("numerek interesanta poprawny\n" << flush);
                }
                
            } break;
            case 3: { // obsluz()
                //debug("obsluz\n" << flush);
                int k = randint(0, m - 1);
                interesant* i = obsluz(k);
                
                debug("obsluz dla k = " << k << ": " << flush);
                
                if(kolejki[k].empty()) {
                    assert(i == NULL);
                    debug("kolejka pusta\n" << flush);
                } else {
                    assert(i == daj_interesanta[kolejki[k][0]]);
                    debug("zdejmuje " << numerek(i) << " z kolejki " << k << "\n" << flush);
                    reverse(kolejki[k].begin(), kolejki[k].end());
                    kolejki[k].pop_back();
                    reverse(kolejki[k].begin(), kolejki[k].end());
                    
                    interesanci_w_okienkach.erase(interesanci_w_okienkach.find(numerek(i)));
                }
                
            } break;
            case 4: { // zmiana_okienka()
                //debug("zmiana okienka\n" << flush);
                if(interesanci_w_okienkach.empty() || m == 1) {
                    q++;
                    continue;
                } else {
                    int ind = randint(0, (int)interesanci_w_okienkach.size()- 1);
                    auto itt = interesanci_w_okienkach.begin();
                    advance(itt, ind);
                    
                    auto it = daj_interesanta.find(*itt);
                    
                    debug("zmieniam okienko interesanta o numerku " << it->first << "\n" << flush);
                    
                    int num = it->first;
                    bool good = false;
                    for(int i = 0; i < m; i++) {
                        auto ittt = find(kolejki[i].begin(), kolejki[i].end(), num);
                        if(ittt != kolejki[i].end()) {
                            int k = randint(0, m - 1);
                            while(k == i)
                                k = randint(0, m - 1);
                            
                            debug("znalazlem interesanta przy okienku " << i << "\n" << flush);
                            
                            debug("przenosze go do okienka " << k << "\n" << flush);
                            
                            zmiana_okienka(it->second, k);
                            kolejki[i].erase(ittt);
                            kolejki[k].push_back(it->first);
                            
                            good = true;
                            
                            break;
                        }
                    }
                    
                    assert(good);
                }
            
            } break;
            case 5: { // zamkniecie_okienka()
                debug("zamkniecie okienka\n" << flush);
                if(m == 1) {
                    q++;
                    continue;
                } else {
                    int k1 = randint(0, m - 1);
                    int k2 = randint(0, m - 1);
                    while(k1 == k2)
                        k2 = randint(0, m - 1);
                    
                    zamkniecie_okienka(k1, k2);
                    
                    debug("zamykam okienko " << k1 << " i przenosze wszystkich do " << k2 << "\n" << flush);
                    
                    reverse(kolejki[k1].begin(), kolejki[k1].end());
                    while(!kolejki[k1].empty()) {
                        kolejki[k2].push_back(kolejki[k1].back());
                        kolejki[k1].pop_back();
                    }
                }
                
            } break;
            case 6: { // fast_track()
                debug("fast_track\n" << flush);
                int k = randint(0, m - 1);
                if(kolejki[k].empty()) {
                    q++;
                    continue;
                } else {
                    int a = randint(0, (int)kolejki[k].size() - 1);
                    int b = randint(a, (int)kolejki[k].size() - 1);
                    
                    debug("fast track dla kolejki " << k << "\n" << flush);
                    debug("pierwszy interesant to " << kolejki[k][a] << " ostatni to " << kolejki[k][b] << "\n" << flush);
                    
                    interesant *i1 = daj_interesanta[kolejki[k][a]];
                    interesant *i2 = daj_interesanta[kolejki[k][b]];
                    vector<interesant *> v = fast_track(i1, i2);
                    
                    vector<interesant *> w;
                    for(int i = a; i <= b; i++) {
                        interesanci_w_okienkach.erase(interesanci_w_okienkach.find(kolejki[k][i]));
                        w.push_back(daj_interesanta[kolejki[k][i]]);
                    }
                    
                    assert(w == v);
                    
                    kolejki[k].erase(kolejki[k].begin() + a, kolejki[k].begin() + b + 1);
                }
                
            } break;
            case 7: { // naczelnik()
                debug("naczelnik\n" << flush);
                int k = randint(0, m - 1);
                naczelnik(k);
                debug("naczelnik, odwracam kolejke " << k << "\n" << flush);
                reverse(kolejki[k].begin(), kolejki[k].end());
            } break;
        
        }
        
        
        debug("\nstan kolejek:\n");
        for(int i = 0; i < m; i++) {
            debug(i << ": ");
            for(int x : kolejki[i])
                debug(x << " ");
            debug("\n" << flush);
        }
        debug("\n" << flush);
        
    
    }

    //cout << "here\n" << flush;
    //show_kolejki();
    vector<interesant *> v = zamkniecie_urzedu();

    //cout << "here2\n" << flush;
    
    vector<interesant *> pozostali;
    for(int i = 0; i < m; i++) {
        reverse(kolejki[i].begin(), kolejki[i].end());
        while(!kolejki[i].empty()) {
            pozostali.push_back(daj_interesanta[kolejki[i].back()]);
            kolejki[i].pop_back();
        }
    }
    
    assert(v == pozostali);
    
    for(auto [num, interesant] : daj_interesanta) {
        assert(num == numerek(interesant));
    }
    
    for(auto [num, interesant] : daj_interesanta) {
        free(interesant);
    }
    
    return 0;
}
