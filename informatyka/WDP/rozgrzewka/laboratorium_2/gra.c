#include <stdio.h>

int graj(int a,int b){
   if(a == 1  && b == 1){
      return 0;
   }
   else if((a+b) % 2 == 0){
      if(a!= 1){
         return 1;
      }
      else{
         return 2;
      }
   }
   else{
      if(a % 2 == 0){
         return 1;
      }else{
         return 2;
      }
   }
}