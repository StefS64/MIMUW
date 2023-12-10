#include <bits/stdc++.h>
using namespace std;
int random(int a, int b){
   return a + rand()%(b-a+1);
}
int main(){
   int seed;
   cin >> seed;
   srand(seed);
   int n = random(1, 10000);
   int Min = 0;
   cout << n<<endl;
   for(int i = 0;i < n; i++){
      cout << random(1,n)<<" ";
      Min = random(Min,10  *n);
      cout << Min <<endl;
   }
}
