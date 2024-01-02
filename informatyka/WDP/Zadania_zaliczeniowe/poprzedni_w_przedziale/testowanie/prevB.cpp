// autor: Grzegorz Krawczyk
#include <bits/stdc++.h>
#include "prev.h"
using namespace std;
vector<int> v;

void init(const std::vector<int> &seq)
{
    v = seq;
}
int prevInRange(int i, int lo, int hi) // max{ j : 0 <= j <= i && seq[j] \in [lo..hi] } or -1
{
    int ret = -1;
    for(int j = 0; j <= i; j++)
        if(lo <= v[j] && v[j] <= hi) ret = j;
    return ret;
}
void pushBack(int value)
{
    v.push_back(value);
}
void done()
{
    v.clear();
}