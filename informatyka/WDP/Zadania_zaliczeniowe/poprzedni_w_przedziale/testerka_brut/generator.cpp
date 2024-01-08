#include <bits/stdc++.h>
using namespace std;
const long long MIN = INT_MIN, MAX = INT_MAX;
long long random(long long a, long long b){
   return a + rand()%(b-a+1);
}
int main(){
   int seed;
   cin >> seed;
   srand(seed);
   long long n = random(1, 10000);
   long long q = random(1, 100000);
   cout << n<<" "<<q<<endl;
   for(long long i = 0; i< n; i++){
      cout<<random(MIN,MAX)<<" ";
   }cout<<endl;
   long long co;
   long long lo;
   for(long long i = 0; i < q; i++){
      co = random(0,2);
      if(co > 1){
         cout <<"q "<<random(0,n-1);
         lo = random(MIN,MAX);
         cout <<" "<<lo<<" "<<random(lo,MAX)<<endl;
      }else{
         cout <<"a "<<random(MIN,MAX)<<endl;
         n++;
      }
   }
}
