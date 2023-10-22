#include "gra.h"
#include <stdio.h>
#include <stdlib.h>
int gcd(int a, int b) {
  while (a != b) {
    if (a > b) {
      a -= b;
    } else {
      b -= a;
    }
  }
  return a;
}
int a,b;
void update_a_b() {
   int temp = gcd(a, b);
   a /= temp;
   b /= temp;
}
int main() {
  int n, input_number = 0;
  char move;

  printf("DIVIDING NUMBERS THE GAME\n");
  printf("\nENTER THE SIZE OF THE GAME: ");

  input_number = scanf("%d", &n);
  a = rand() % n;
  b = rand() % n;

  printf("\nYOUR STARTING NUMBER:  a: %d b: %d\n", a, b);
  update_a_b();
  printf("YOU START INPUT a or b to alter the value of the numbers by one\n");
  while(a != 0){
      if (a == 1 && b == 1) {
         printf("a: %d, b: %d \n\n", a,b);
         printf(" a == b == 1 YOU LOST\n");
         return 0;
      } else {
         printf("a: %d, b: %d \n\n", a,b);
         printf("YOUR TURN: \n");    
         input_number += scanf(" %c", &move);
         if (move == 'a') {
            a--;
         } else if (move == 'b') {
            b--;
         } else {
            printf("INVALID INPUT. YOU ENTERED /%c/ TRY AGAIN \n INPUT a or b: ", move);
         }
         if(move == 'a' || move == 'b'){
            update_a_b();
            printf("a: %d, b: %d \n\n", a,b);
            printf("OPONENTS TURN:\n");
            switch (graj(a, b)) {
            case 1:
               a--;
               printf("a\n");
               break;
            case 2:
               b--;
               printf("b\n");
               break;
            case 0:
               printf("YOU WON");
               return 0;
               break;
            }
            update_a_b();
         }
      }
  }
}