#include <math.h>
#include "stdbool.h"
#include <stdio.h>
#include "ary.h"
const double EPSILON = 1e-10;

// --------------------------------------------- //
// CODE REVIEW ROBIONE PRZEZ GRZEGORZA JUSZCZYKA //
// --------------------------------------------- //


bool czy_zero(double x) {
   return fabs(x) < EPSILON; 
}



//min iloczynów wszystkich par (a,b)X(c,d)
double min2x2(double a, double b, double c, double d){//max iloczynów ze zbioru: (a,b)x(c,d).
   return fmin(a*c, fmin(b*c, fmin(a*d, b*d)));
}



//max iloczynów wszystkich par (a,b)X(c,d)
double max2x2(double a, double b, double c, double d){
   return fmax(a*c, fmax(b*c, fmax(a*d, b*d)));
}



wartosc stworz(double x, double y, bool anty, bool nan){
   wartosc generator;
   generator.x = x;
   generator.y = y;
   generator.czy_anty = anty;
   generator.czy_nan = nan;
   return generator;
}



wartosc wartosc_dokladnosc(double x, double p){
   return stworz((x - p*(double)fabsl(x)/100), (x + p*(double)fabsl(x)/100), 0, 0);
}



wartosc wartosc_od_do(double x, double y){
   double srednia = (x + y)/2, roznica = (y - x)/2;/*wiemy że y > x*/
   return stworz(srednia - roznica, srednia + roznica, 0, 0);
}



wartosc wartosc_dokladna(double x){
   return stworz(x, x, 0, 0);
}



bool in_wartosc(wartosc w, double x){
   if(w.czy_anty &&  (x < w.x + EPSILON || x > w.y - EPSILON)){
      return 1;
   }
   else if(!w.czy_anty && (-1*EPSILON + w.x < x && x < EPSILON + w.y)){
      return 1;
   }
   return 0;
}



double min_wartosc(wartosc w){
   if(w.czy_anty){
      return -HUGE_VAL;
   }
   else if(!w.czy_nan){
      if((bool)isinf(w.x)){//isinf typu bool niech będzie true lub false nie ma specyfikacji, że isinf(-HUGE_VAL) = -1
         return -HUGE_VAL;
      }
      return w.x;
   }
   else{
      return NAN;
   }
}



double max_wartosc(wartosc w){
   if(w.czy_anty){
      return HUGE_VAL;
   }
   else if(!w.czy_nan) {
      if((bool)isinf(w.y)){
         return HUGE_VAL;
      }
      return w.y;
   }
   else{
      return NAN;
   }
}



double sr_wartosc(wartosc w){
   if(!w.czy_anty){
      return (w.x + w.y)/2;
   }
   else {//jest antyprzedziałem lub jest NANEM
      return NAN;
   }
}



void swap(wartosc *a, wartosc *b){
   wartosc tymczasowa  = *a;
   *a = *b;
   *b = tymczasowa;
}


wartosc przekarz_nan(){// funkcja odpowiadająca za przekazywanie dalej NANa unika operacji na nanach.
   return stworz(NAN, NAN, 0, 1);
}


wartosc plus(wartosc a, wartosc b){
   wartosc suma;
   if(a.czy_nan || b.czy_nan){
      return przekarz_nan();
   }
   if(!a.czy_anty && !b.czy_anty){
      suma = stworz(a.x + b.x, a.y + b.y, 0, 0);
   }
   else if(a.czy_anty && b.czy_anty){
      suma = stworz(-HUGE_VAL, HUGE_VAL, 0, 0);
   }
   else {//sumujemy antyprzedzial z przedzialem (najpierw anty)
      if(!a.czy_anty){
         swap(&a, &b);
      }
      suma = stworz(a.x + b.y, a.y + b.x, 1, 0);
      if(suma.x >= suma.y - EPSILON){//jeżeli po sumie się pokrywają uzyskujemy cały obszar
         suma = stworz(-HUGE_VAL, HUGE_VAL, 0, 0);
      }
   }
   return suma;
}



wartosc minus(wartosc a, wartosc b){
   if(a.czy_nan || b.czy_nan){
      return przekarz_nan();
   }
   b = stworz(-b.y, -b.x, b.czy_anty, b.czy_nan);
   return plus(a, b);
}


wartosc razy(wartosc a, wartosc b){
   wartosc iloczyn;
   if(a.czy_nan || b.czy_nan){//czy NAN
      return przekarz_nan();
   }
   if(!a.czy_anty && !b.czy_anty){
      if((czy_zero(a.x) && czy_zero(a.y)) || (czy_zero(b.x) && czy_zero(b.y))){//czy któryś jest zerem
         iloczyn = stworz(0.0, 0.0, 0, 0);
      }
      else{
         iloczyn = stworz(min2x2(a.x, a.y, b.x, b.y), max2x2(a.x, a.y, b.x, b.y), 0, 0);
      }
   }
   else if(a.czy_anty && b.czy_anty){//2 anty przedziały
      if(in_wartosc(a, 0) || in_wartosc(b, 0)){
         iloczyn = stworz(-HUGE_VAL, HUGE_VAL, 0, 0);
      }
      else {//nie zawiera zera więc nie mogą być dowolnie małe oraz a.x < 0 < a.y i b.x < 0 < b.y
         iloczyn = stworz(fmax(a.x * b.y, b.x * a.y), fmin(a.x * b.x, b.y * a.y), 1, 0);
      }
   }
   else {
      if(!a.czy_anty){//a jest zawsze antyprzedziałem 
         swap(&a, &b);
      }

      if(czy_zero(b.x) && czy_zero(b.y)){//b jest zerem;
         iloczyn = stworz(0.0, 0.0, 0, 0);
      }
      else if(in_wartosc(b, 0)){//jeżeli b zawiera zero
         iloczyn = stworz(-HUGE_VAL, HUGE_VAL, 0, 0);
      }
      else if(in_wartosc(a, 0)){//b nie zawiera 0 ale 'a' zawiera
         if((bool)isinf(b.x) && (bool)isinf(b.y)){//b jest całym przedziałem//ten if może być useless
            iloczyn = stworz(-HUGE_VAL, HUGE_VAL, 0, 0);
         }
         else if((bool)isinf(b.x)){//b nie ma lewej granicy
            if(czy_zero(a.x)){//a ma granice lewą w zerze (uzyskujemy dowolnie bliskie prawej strony)
               iloczyn = stworz(b.y*a.y, 0.0, 1, 0);
            }
            else if (czy_zero(a.y)){//prawy kraniec antyprzedzialu to zero
               iloczyn = stworz(0.0, b.y*a.x, 1, 0);
            }
            else {//żaden z krańców to nie zero
               iloczyn = stworz(b.y*a.y, a.x*b.y, 1, 0);
            }
         }
         else if((bool)isinf(b.y)){
            if(czy_zero(a.x)){//lewy kraniec antyprzedziału to zero.
               iloczyn = stworz(0, b.x*a.y, 1, 0);
            }
            else if (czy_zero(a.y)){//prawy kraniec antyprzedzialu to zero
               iloczyn = stworz(b.x*a.x, 0.0, 1, 0);
            }
            else {//żaden z krańców to nie zero
               iloczyn = stworz(b.x*a.x, a.y*b.x, 1, 0);
            }
         } 
         else {// a zawiera zero i jest antyprzedziałem oraz b jest zwykłym przedziałem (bez inf i zera)
            if(b.x > EPSILON){//czy b ma same wartości dodatnie
               iloczyn = stworz(fmax(a.x*b.x, a.x*b.y), fmin(a.y*b.x, a.y*b.y), 1, 0);
            }
            else{
               iloczyn = stworz(fmax(a.y*b.x, a.y*b.y), fmin(a.x*b.x, a.x*b.y), 1, 0);
            }
         }
      }
      else {//a ani b nie zwierają zera
         if(b.x > EPSILON){//przedział o wyrazach dodatnich
            iloczyn = stworz(a.x*fmin(b.x, b.y), a.y*fmin(b.x, b.y), 1, 0);
         }
         else{
            iloczyn = stworz(a.y*fmax(b.x, b.y), a.x*fmax(b.x, b.y), 1, 0);
         }
      }
   }
   if(iloczyn.x >= iloczyn.y-EPSILON && iloczyn.czy_anty){//jeżeli po sumie się pokrywają uzyskujemy cały obszar
      iloczyn = stworz(-HUGE_VAL, HUGE_VAL, 0, 0);
   }
   return iloczyn;
}



wartosc odwrotnosc(wartosc a){
   wartosc odwrotny;
   if(a.czy_nan){
      return przekarz_nan();
   }
   if(czy_zero(a.x) && czy_zero(a.y)){//jeżeli a jest zerem to NAN;
      return przekarz_nan();
   }
   else if(!a.czy_anty){//a jest zwykłym przedziałem
      if(in_wartosc(a,0)){ // a zawiera 0
         if((bool)isinf(a.x)){// a nie ma lewego krańca
            if(czy_zero(a.y) || (bool)isinf(a.y)){//(-inf,0] oraz (-inf,inf) przechodzi na sam siebie
               return a;
            }
            else {//(-inf,a]
               odwrotny = stworz(0.0, 1/a.y, 1, 0);
            }
         }
         else if((bool)isinf(a.y)){// a nie ma prawego krańca
            if(czy_zero(a.x)){//[0,inf]
               return a;
            }
            else {//[a,inf]
               odwrotny = stworz(0.0, 1/a.x, 1, 0);
            }
         }
         else {//przedział ma oba krańce i zawiera 0;
            if(czy_zero(a.x)){//[0,a] a > 0
               odwrotny = stworz(1/a.y, HUGE_VAL, 0, 0);
            }
            else if (czy_zero(a.y)){//[a,0] a < 0
               odwrotny = stworz(-HUGE_VAL, 1/a.x, 0, 0);
            }
            else {//[a,b] ( a < 0 < b)
               odwrotny = stworz(1/a.x, 1/a.y, 1, 0);
            }
         }
      }
      else {// a nie zawiera 0;
         if((bool)isinf(a.x)){//(-inf,a] a < 0;
            odwrotny = stworz(1/a.y, 0.0, 0, 0);
         }
         else if((bool)isinf(a.y)){//[a,inf) a > 0;
            odwrotny = stworz(0.0, 1/a.x, 0, 0);
         }
         else {//przedział ma oba krańce i  nie zawiera 0 [a,b] (a < b < 0 lub 0 < a < b);
            odwrotny = stworz(1/a.y, 1/a.x, 0, 0);
         }
      }
   }
   else{//jest antyprzedziałem
      if(in_wartosc(a,0)){//zawiera zero;
         if(czy_zero(a.x)){//(-inf,0]+[y,inf) y > 0(//(-inf,0]+[0,inf) - nigdy nie zajdzie bo cały reprezentujemy poprzez (-inf,inf))
            odwrotny = stworz(-HUGE_VAL, 1/a.y, 0, 0);
         }
         else if (czy_zero(a.y)){//(-inf,x]+[0,inf) x < 0
            odwrotny = stworz(1/a.x, HUGE_VAL, 0, 0);
         }
         else if(a.x > EPSILON){//(-inf,x]+[y,inf) 0 < x < y
            odwrotny = stworz(1/a.y, 1/a.x, 1, 0);
         }
         else if(a.y < EPSILON){//(-inf,x]+[y,inf) x < y < 0
            odwrotny = stworz(1/a.y, 1/a.x, 1, 0);
         }
      }
      else {//(-inf,x]+[y,inf) x < 0 < y
         odwrotny = stworz(1/a.x, 1/a.y, 0, 0);
      }
   }
   odwrotny.czy_nan = 0;
   return odwrotny;
}



wartosc podzielic(wartosc a, wartosc b){
   if(a.czy_nan || b.czy_nan){
      return przekarz_nan();
   }
   return razy(a,odwrotnosc(b));
}



void cout(wartosc a){
   printf("%.10lf %.10lf %d %d\n", a.x, a.y, a.czy_anty, a.czy_nan);
}
// --------------------------------------------- //
// CODE REVIEW ROBIONE PRZEZ GRZEGORZA JUSZCZYKA //
// --------------------------------------------- //
