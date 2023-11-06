#include <stdio.h>
int stopien(int n){
   if(n == 0){
      return -1;
   }
   for(int i = 0; i < n; i++){
      if((n & (1 << i)) == (1 << i)){
         return i;
      }
   }
   return -1;
}

int main(){
   int n;
   if(scanf("%d", &n)){};
   printf("%d", stopien(n));

}