#include <stdio.h>

int bin_search(int a, int T[],int n){
   int l = -1, r = n-1;//l - liczba mniejsza od szukanej
   while(l < r-1){
      int mid = (l+r)/2;
      if(a <= T[mid]){
         r = mid;
      }else{
         l = mid;
      }
   }
   return r;
}

int main(){
   int T[9] = {1,2,3,4,4,6,6,7};
   printf("%d", bin_search(5,T,9));
}