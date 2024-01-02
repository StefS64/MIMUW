// autor: Grzegorz Krawczyk
#include <bits/stdc++.h>
#include "prev.h"
using namespace std;
#define rep(a,b) for(int a=0;a<(b);a++)
///flagi kompilacji:
///g++ -std=c++17 -static -Wall -pedantic -O3 -s -lm -o prevG prevG.cpp

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int _, n;
    cin >> _ >> n;
    vector<int> V(n);
    rep(i, n) cin >> V[i];
    init(V);
    while(_--)
    {
        char op;
        cin >> op;
        //cerr << op << ' ';
        if(op == 'A')
        {
            int v;
            cin >> v;
            pushBack(v);
        }
        else
        {
            int i, lo, hi;
            cin >> i >> lo >> hi;
            cout << prevInRange(i, lo, hi) << '\n';
        }
    }
    done();
}
