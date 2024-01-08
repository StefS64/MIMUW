#include <iostream>
#include <vector>
using namespace std;


int main(){
   int n, q;
   cin >> n >> q;
   std::vector<int>liczby;
   int nowy;
   for(int i = 0; i < n ;i ++){
      cin >> nowy;
      liczby.push_back(nowy);
   }
   char co;
   int a, lo,hi;
   for(int i = 0; i < q ;i ++){
      cin >> co;
      if(co == 'a'){
         cin >> nowy;
         liczby.push_back(nowy);
      }else if (co == 'q'){
         cin >> a >> lo >> hi;
         while(a >= 0){
            if(liczby[a]>=lo && liczby[a]<= hi){
               cout <<a<<'\n';
               a = -1;
            }
            a--;
         }
         if(a == -1){
            cout <<-1<<'\n';
         }
      }
   }
}