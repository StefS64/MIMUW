#include <stdio.h>
#include <stdlib.h>
void cout(int n, int *T){
   for(int i = 0; i < n; i++){
      printf("%d ",T[i]);
   }printf("\n");
}
int gorka_jedynek(int n, int *A){
   //int *pre = malloc(sizeof(int)*n+1);
   int *ilosc_roznicy = malloc(sizeof(int)*(long unsigned int)(n+1));
   int *roznica = malloc(sizeof(int)*(long unsigned int)(n+1));
   int sum0 = 0,sum1 = 0;
   for(int i = n + 1; i  >= 0; i--){
      roznica[i] = 0;
      ilosc_roznicy[i] = 0;
   }
   for(int i = n-1; i  >= 0; i--){
      roznica[i] = roznica[i+1];
      if(A[i] == 1){
         roznica[i]++;
         sum1++;
      }else{
         roznica[i]--;
         sum0++;
      }
      if(roznica[i] > 0){
         ilosc_roznicy[roznica[i]]++;
      }
   }
   cout(n, roznica);
   cout(n, ilosc_roznicy);
   int odpoc0 = 0, odpoc1 = 0;
   int p = -1;
   for(int i = 0 ; i < n; i++){
      if(roznica[i] > 0){
         ilosc_roznicy[roznica[i]]--;
      }
      if(A[i] == 1){
         odpoc1++;
      }else{
         odpoc0++;
      }
      if(odpoc0  > odpoc1 && (odpoc0 - odpoc1 + sum1 - sum0) > 0 && ilosc_roznicy[odpoc0 - odpoc1 + sum1 - sum0] > 0 ){
         p = i;
         break;
      }
   }
   return p;
}
int main(){
   int A[6] = {0,0,0,0,1,1};
   printf("%d", gorka_jedynek(6, A));
}