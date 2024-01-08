// autor: Grzegorz Krawczyk
#include <bits/stdc++.h>
using namespace std;
#define rep(a,b) for(int a=0;a<(b);a++)
///flagi kompilacji:
///g++ -std=c++17 -static -Wall -pedantic -O3 -s -lm -o prevG prevG.cpp
int p(long long a, long long b){
	return a + (2*(long long)rand() + (long long)rand()%2) % (b-a+1);
}

const int MAX_OP = 1000; // maksymalna liczba operacji w teście
const int MIN_VAL = INT_MIN; // minimalna wartość w ciągu w teście
const int MAX_VAL = INT_MAX; // maksymalna wartość w ciągu w teście
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
	int Z;
	cin >> Z;
	srand(Z);

	int N = p(3, MAX_OP); // liczba operacji
	cout << N << '\n';

	int n = p(1, MAX_OP); // długość początkowego ciągu
	cout << n << '\n' << p(MIN_VAL, MAX_VAL);
	rep(i, n-1) cout << ' ' << p(MIN_VAL, MAX_VAL);
	cout << '\n';

	rep(j, N) // kolejne operacje
	{
		int op = p(1, 3);
		// pushBack(int v)
		if(op <= 1) // 1/3 szansy
		{
			int v = p(MIN_VAL, MAX_VAL);
			cout << "A " << v << "\n";
			n++;
		}
		// prevInRange(int i, int lo, int hi)
		else // 2/3 szansy
		{
			int i = p(0, n-1);
			int lo = p(MIN_VAL, MAX_VAL);
			int hi = p(MIN_VAL, MAX_VAL);
			if(lo > hi) swap(lo, hi);
			cout << "Q " << i << ' '<< lo << ' ' << hi << '\n';
		}
	}
    return 0;
}
