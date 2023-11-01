
#include <math.h>
#include "stdbool.h"
#include <stdio.h>
#include "ary.h"
const double EPSILON = 1e-10;

// --------------------------------------------- //
// CODE REVIEW ROBIONE PRZEZ GRZEGORZA JUSZCZYKA //
// --------------------------------------------- //
void cout(wartosc a);


bool czy_zero(double x) {
   return fabs(x) < EPSILON; 
}



//min iloczynów wszytstkich par (a,b)X(c,d)
double min2x2(double a, double b, double c,double d){//max iloczynów ze zbioru: (a,b)x(c,d).
   return fmin(a*c,fmin(b*c,fmin(a*d,b*d)));
}



//max iloczynów wszytstkich par (a,b)X(c,d)
double max2x2(double a, double b, double c,double d){
   return fmax(a*c,fmax(b*c,fmax(a*d,b*d)));
}



wartosc wartosc_dokladnosc(double x, double p){
   wartosc przedzial;
   przedzial.x = (x - p*(double)fabsl(x)/100);
   przedzial.y = (x + p*(double)fabsl(x)/100);
   przedzial.czy_nan = 0;
   przedzial.czy_anty = 0;
   return przedzial;
}



wartosc wartosc_od_do(double x, double y){
   wartosc przedzial;
   double srednia = (x+y)/2, roznica = (y-x)/2;/*wiemy że y > x*/
   przedzial.x = srednia - roznica;
   przedzial.y = srednia + roznica;
   przedzial.czy_nan = 0;
   przedzial.czy_anty = 0;
   return przedzial;
}



wartosc wartosc_dokladna(double x){
   wartosc przedzial;
   przedzial.x = x;
   przedzial.y = x;
   przedzial.czy_nan = 0;
   przedzial.czy_anty = 0;
   return przedzial;
}



bool in_wartosc(wartosc w, double x){
   if(w.czy_anty == 1 &&  (x < w.x  + EPSILON || x > w.y - EPSILON)){
      return 1;
   }
   else if(w.czy_anty == 0 && (-1*EPSILON + w.x < x && x < EPSILON + w.y)){
      return 1;
   }
   return 0;
}



double min_wartosc(wartosc w){
   if(w.czy_anty == 1){
      return -HUGE_VAL;
   }
   else if(w.czy_nan == 0){
      if((bool)isinf(w.x) == 1){
         return -HUGE_VAL;
      }
      return w.x;
   }
   else{
      return NAN;
   }
}



double max_wartosc(wartosc w){
   if(w.czy_anty == 1){
      return HUGE_VAL;
   }
   else if(w.czy_nan == 0) {
      if((bool)isinf(w.y) == 1){
         return HUGE_VAL;
      }
      return w.y;
   }
   else{
      return NAN;
   }
}



double sr_wartosc(wartosc w){
   if(w.czy_anty == 0){
      return (w.x+w.y)/2;
   }
   else {//jest antyprzedziałem lub jest NANEM
      return NAN;
   }
}



void swap(wartosc *a,  wartosc *b){
   wartosc tymczasowa  = *a;
   *a = *b;
   *b = tymczasowa;
}


wartosc update_nan(){
   wartosc w;
   w.x = NAN;
   w.y = NAN;
   w.czy_nan = 1;
   w.czy_anty = 0;
   return w;
}



wartosc plus(wartosc a, wartosc b){
   wartosc suma;
   if(a.czy_nan == 1 || b.czy_nan == 1){
      return update_nan();
   }
   if(a.czy_anty == 0 && b.czy_anty == 0){
      suma.x = a.x + b.x;
      suma.y = a.y + b.y;
      suma.czy_anty = 0;
   }
   else if(a.czy_anty == 1 && b.czy_anty == 1){
      suma.x = -HUGE_VAL;
      suma.y = HUGE_VAL;
      suma.czy_anty = 0;
   }
   else {//sumujemy antyprzedzial z przedzialem (najpierw anty)
      if(a.czy_anty == 0){
         swap(&a,&b);
      }
      suma.x = a.x + b.y;
      suma.y = a.y + b.x;
      suma.czy_anty = 1;
      if(suma.x >= suma.y-EPSILON){//jeżeli po sumie się pokrywają uzyskujemy cały obszar
         suma.x = -HUGE_VAL;
         suma.y = HUGE_VAL;
         suma.czy_anty = 0;
      }
   }
   suma.czy_nan = 0;
   return suma;
}



wartosc minus(wartosc a, wartosc b){
   if(a.czy_nan == 1 ||b.czy_nan == 1){
      return update_nan();
   }
   b.x *=-1;
   b.y *=-1;
   double tymczasowy = b.x;
   b.x = b.y;
   b.y = tymczasowy;
   return plus(a,b);
}


wartosc razy(wartosc a, wartosc b){
   wartosc iloraz;
   if(a.czy_nan == 1 ||b.czy_nan == 1){//czy NANprint
      return update_nan();
   }
   if(a.czy_anty == 0 && b.czy_anty == 0){
      if((fabs(a.x) <= EPSILON && fabs(a.y) <= EPSILON) || (fabs(b.x) <= EPSILON && fabs(b.y) <= EPSILON)){//czy któryś jest zerem
         iloraz.x = 0.0;
         iloraz.y = 0.0;
         iloraz.czy_anty = 0;
         iloraz.czy_nan = 0;
      }
      else{
         iloraz.x = min2x2(a.x, a.y, b.x, b.y);
         iloraz.y = max2x2(a.x, a.y, b.x, b.y);
         iloraz.czy_anty = 0;
      }
   }
   else if(a.czy_anty == 1 && b.czy_anty == 1){//2 anty przedziały
      if(in_wartosc(a, 0)== 1 || in_wartosc(b, 0) == 1){
         iloraz.x = -HUGE_VAL;
         iloraz.y = HUGE_VAL;
         iloraz.czy_anty = 0;
      }
      else {//nie zawiera zera więc nie mogą być dowolnie małe oraz a.x < 0 < a.y i b.x < 0 < b.y
         iloraz.x = fmax(a.x * b.y, b.x * a.y);
         iloraz.y = fmin(a.x * b.x, b.y * a.y);
         iloraz.czy_anty = 1;
      }
   }
   else {
      //printf("a anty przedzial b nie jest\n");
      if(a.czy_anty == 0){//a jest zawsze antyprzedziałem 
         swap(&a, &b);
      }

      if(fabs(b.x) <= EPSILON && fabs(b.y) <= EPSILON){//b jest zerem;
         iloraz.x = 0.0;
         iloraz.y = 0.0;
         iloraz.czy_anty = 0;
         iloraz.czy_nan = 0;
      }
      else if(in_wartosc(b,0) == 1){//jeżeli b zawiera zero
         iloraz.x = -HUGE_VAL;
         iloraz.y = HUGE_VAL;
         iloraz.czy_anty = 0;
      }
      else if(in_wartosc(a,0) == 1){//b nie zawiera 0 ale 'a' zawiera
         //printf("a zawiera zero a b nie\n");
         if((bool)isinf(b.x) == 1 && (bool)isinf(b.y) == 1){//b jest całym przedziałem//ten if może być useless
            iloraz.x = -HUGE_VAL;
            iloraz.y = HUGE_VAL;
            iloraz.czy_anty = 0;
         }
         else if((bool)isinf(b.x) == 1){//b nie ma lewej granicy
            if(fabs(a.x) <= EPSILON){//a ma granicy lewej w zerze (uzyskujemy dowolnie bliskie prawej strony)
               iloraz.x = b.y*a.y;
               iloraz.y = 0;
               iloraz.czy_anty = 1;
            }
            else if (fabs(a.y) <= EPSILON){//prawy kraniec antyprzedzialu to zero
               iloraz.x = 0;
               iloraz.y = b.y*a.x;
               iloraz.czy_anty = 1;
            }
            else {//żaden z krańców to nie zero
               //printf("tutaj\n");
               iloraz.x = a.y*b.y;
               iloraz.y = a.x*b.y;
               iloraz.czy_anty = 1;
            }
         }
         else if((bool)isinf(b.y) == 1){
            if(fabs(a.x) <= EPSILON){//lewy kraniec antyprzedziału to zero.
               iloraz.x = 0;
               iloraz.y = b.x*a.y;
               iloraz.czy_anty = 1;
            }
            else if (fabs(a.y) <= EPSILON){//prawy kraniec antyprzedzialu to zero
               iloraz.y = 0;
               iloraz.x = a.x*b.x;
               iloraz.czy_anty = 1;
            }
            else {//żaden z krańców to nie zero
               iloraz.x = a.x*b.x;
               iloraz.y = a.y*b.x;
               iloraz.czy_anty = 1;
            }
         } 
         else {// a zawiera zero i jest antyprzedziałem oraz b jest zwykłym przedziałem (bez inf i zera)
            if(b.x > 0.0){
               iloraz.x = fmax(a.x*b.x, a.x*b.y);
               iloraz.y = fmin(a.y*b.x, a.y*b.y);
               iloraz.czy_anty = 1;
            }
            else{
               iloraz.x = fmax(a.y*b.x, a.y*b.y);
               iloraz.y = fmin(a.x*b.x, a.x*b.y);
               iloraz.czy_anty = 1;
            }
         }
      }
      else {//a ani b nie zwierają zera
         if(b.x > EPSILON){
            iloraz.x = a.x*fmin(b.x, b.y);
            iloraz.y = a.y*fmin(b.x, b.y);
            iloraz.czy_anty = 1;
            //printf("siema");
         }
         else{
            //printf("siema");
            iloraz.x = a.y*fmax(b.x, b.y);
            iloraz.y = a.x*fmax(b.x, b.y);
            iloraz.czy_anty = 1;
         }
         
         //printf("debug doszło");
      }
   }
   if(iloraz.x >= iloraz.y-EPSILON && iloraz.czy_anty == 1){//jeżeli po sumie się pokrywają uzyskujemy cały obszar
      iloraz.x = HUGE_VAL;
      iloraz.y = -HUGE_VAL;
      iloraz.czy_anty = 0;
   }
   iloraz.czy_nan = 0;
   return iloraz;
}



wartosc odwrotnosc(wartosc a){
   wartosc odwrotny;
   if(a.czy_nan == 1){
      return update_nan();
   }
   if(fabs(a.x) <= EPSILON && fabs(a.y) <= EPSILON){//jeżeli a jest zerem to NAN;
      return update_nan();
   }
   else if(a.czy_anty == 0){//a jest zwykłym przedziałem
      if(in_wartosc(a,0) == 1){ // a zawiera 0
         if((bool)isinf(a.x) == 1){// a nie ma lewego krańca
            if(fabs(a.y) <= EPSILON || (bool)isinf(a.y) == 1){//(-inf,0] oraz (-inf,inf) przechodzi na sam siebie
               return a;
            }
            else {//(-inf,a]
               odwrotny.x = 0;
               odwrotny.y = 1/a.y;
               odwrotny.czy_anty = 1;
            }
         }
         else if((bool)isinf(a.y) == 1){// a nie ma prawego krańca
            if(fabs(a.x) <= EPSILON){//[0,inf]
               return a;
            }
            else {//[a,inf]
               odwrotny.y = 0;
               odwrotny.x = 1/a.x;
               odwrotny.czy_anty = 1;
            }
         }
         else {//przedział ma oba krańce i zawiera 0;
            if(fabs(a.x) <= EPSILON){//[0,a] a > 0
               odwrotny.x = 1/a.y;
               odwrotny.y = HUGE_VAL;
               odwrotny.czy_anty = 0;
            }
            else if (fabs(a.y) <= EPSILON){//[a,0] a < 0
               odwrotny.x = -HUGE_VAL;
               odwrotny.y = 1/a.x;
               odwrotny.czy_anty = 0;
            }
            else {//[a,b] ( a < 0 < b)
               odwrotny.x = 1/a.x;
               odwrotny.y = 1/a.y;
               odwrotny.czy_anty = 1;
               /*printf("debug a:\n");
               cout(a);
               printf("debug odwrotny:");
               cout(odwrotny);*/

            }
         }
      }
      else {// a nie zawiera 0;
         if((bool)isinf(a.x) == 1){//(-inf,a] a < 0;
            odwrotny.x = 1/a.y;
            odwrotny.y = 0;
            odwrotny.czy_anty = 0;
         }
         else if((bool)isinf(a.y) == 1){//[a,inf) a > 0;
            odwrotny.x = 0;
            odwrotny.y = 1/a.x;
            odwrotny.czy_anty = 0;
         }
         else {//przedział ma oba krańce i  nie zawiera 0 [a,b] (a < b < 0 lub 0 < a < b);
            odwrotny.x = 1/a.y;
            odwrotny.y = 1/a.x;
            odwrotny.czy_anty = 0;
         }
      }
   }
   else{//jest antyprzedziałem
      //printf("mam zero\n");
      if(in_wartosc(a,0) == 1){//zawiera zero;
         if(fabs(a.x) <= EPSILON){//(-inf,0]+[y,inf) y > 0(//(-inf,0]+[0,inf) - nigdy nie zajdzie bo cały reprezentujemy poprzez (-inf,inf))
            odwrotny.x = -HUGE_VAL;
            odwrotny.y = 1/a.y;
            odwrotny.czy_anty = 0;
         }
         else if (fabs(a.y) <= EPSILON){//(-inf,x]+[0,inf) x < 0
            odwrotny.x = 1/a.x;
            odwrotny.y = HUGE_VAL;
            odwrotny.czy_anty = 0;
         }
         else if(a.x > EPSILON){//(-inf,x]+[y,inf) 0 < x < y
            odwrotny.x = 1/a.y;
            odwrotny.y = 1/a.x;
            odwrotny.czy_anty = 1;
         }
         else if(a.y < EPSILON){//(-inf,x]+[y,inf) x < y < 0
            odwrotny.x = 1/a.y;
            odwrotny.y = 1/a.x;
            odwrotny.czy_anty = 1;
         }
      }
      else {//(-inf,x]+[y,inf) x < 0 < y
         odwrotny.x = 1/a.x;
         odwrotny.y = 1/a.y;
         odwrotny.czy_anty = 0;
      }
   }
   odwrotny.czy_nan = 0;
   return odwrotny;
}



wartosc podzielic(wartosc a, wartosc b){
   if(a.czy_nan == 1 ||b.czy_nan == 1){
      return update_nan();
   }
   //cout(odwrotnosc(b));
   return razy(a,odwrotnosc(b));
}



void cout(wartosc a){
   printf("%.10lf %.10lf %d %d\n",a.x,a.y,a.czy_anty,a.czy_nan);
}
/*
int main(){
   wartosc ep4;
   ep4.x = 1;
   ep4.y = 7;
   ep4.czy_anty = 1;
   ep4.czy_nan = 0;
   wartosc h = podzielic(wartosc_od_do(1, 2), ep4);
   cout(h);
}
*/
// --------------------------------------------- //
// CODE REVIEW ROBIONE PRZEZ GRZEGORZA JUSZCZYKA //
// --------------------------------------------- //
