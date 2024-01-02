#include <bits/stdc++.h>
using namespace std;
const int MIN = -10, MAX = 10;
int random(int a, int b){
   return a + rand()%(b-a+1);
}
int main(){
   int seed;
   cin >> seed;
   srand(seed);
   int n = random(1, 10);
   int q = random(1, 10);
   cout << n<<" "<<q<<endl;
   for(int i = 0; i< n; i++){
      cout<<random(MIN,MAX)<<" ";
   }cout<<endl;
   int co;
   int lo;
   for(int i = 0; i < q; i++){
      co = random(0,1);
      if(co){
         cout <<"q "<<random(1,n);
         lo = random(MIN,MAX);
         cout <<" "<<lo<<" "<<random(lo,MAX)<<endl;
      }else{
         cout <<"a "<<random(MIN,MAX)<<endl;
         n++;
      }
   }
}