#include <stdio.h>
enum representation {rect,Pol};

struct rectangular {
   double x, y;
};

struct polar{
   double radius, angle;
};

union complex{
   struct rectangular rectan;
   struct polar pola;
};

typedef struct {
   enum representation repr;
   union complex value;
} Complex;
double module(Complex c){
   if(c.repr == Pol){
      return c.value.pola.radius;
   }else{
      return 0.01010101;
   }
}
int main(){
   Complex c , b;
   b.repr = rect;
   b.value.rectan.x = 0.01;
   c.repr = Pol;
   c.value.pola.radius = 3.14;
   c.value.pola.angle = 60;
   struct rectangular X;
   X.x = 0.00001;
   X.y = X.x*2;
   printf("x: %lf y: %lf\n",X.x,X.y);
   printf("c: %lf      d: %lf" ,module(c), module(b));


}