#include <stdio.h>

int main(){
   char q;
   int input = scanf(" %c",&q);
   printf("%c",q);
   input += scanf(" %c",&q);
   printf("%c",q);
}