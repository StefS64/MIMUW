#include <stdio.h>

int minimum (int n, int a[]){
   int l = -1,r = n-1;//l-większy od minimum
   while(l < r-1){
      int mid = (l+r)/2;
      if(a[mid] > a[mid + 1])
         l = mid;
      else
         r = mid;
   }
    printf("halo l: %d, r: %d\n", l , r);
   return a[r];
}
int main(){
   int a[8] = {0,1,1,1,1,4,5,6};
   printf("%d", minimum(8, a));
}