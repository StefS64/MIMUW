#include <stdio.h>
#include <stdlib.h>
int ile_rosnących(int C[], int n){
   int *pre0 = (int*)malloc(sizeof(int)*(long unsigned int)n);
   int *suf2 = (int*)malloc(sizeof(int)*(long unsigned int)n);
    for(int i = 1; i < n; i++){
      pre0[i] = 0;
      suf2[i] = 0;
   } 
   if(C[0] == 0)pre0[0] = 1;
   if(C[n-1] == 2)suf2[n-1] = 1;
  
   for(int i = 1; i < n; i++){
      pre0[i] = pre0[i-1];
      suf2[n-1-i] = suf2[n-i];
      if(C[i] == 0)pre0[i]++;
      if(C[n-1-i] == 2)suf2[n-1-i]++;
   } 
   int ans = 0;
   for(int i = 1; i < n-1; i++){
      if(C[i] == 1){
         ans+=pre0[i]*suf2[i];   
      }
   }
   return ans;
}
int main(){
   int C[6] = {2,2,1,1,0,0};
   printf("%d", ile_rosnących(C,6));

}