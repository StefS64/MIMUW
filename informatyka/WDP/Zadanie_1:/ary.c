#include <stdio.h>
#include <math.h>
//#include <stdlib.h>
#include "stdbool.h"
const double EPSILON = 1e-10;
enum zachowanie_przy_0 {z_lewej,z_prawej,z_obu,nie_zawiera};
typedef struct wartosc {
      double x,y;
      bool czy_anty;/*przedział o krańcach x,y gdzie x <= y lub antyprzedzial*/
      bool czy_nan;//może nie będzie potrzebne ale pewnie będzie
   } wartosc;



bool czy_zero(double x) {
   return fabs(x) < 1e-10; 
}



double min2x2(double a, double b, double c,double d){//max iloczynów ze zbioru: (a,b)x(c,d).
   return fmin(a*c,fmin(b*c,fmin(a*d,b*d)));
}



double max2x2(double a, double b, double c,double d){
   return fmax(a*c,fmax(b*c,fmax(a*d,b*d)));
}



wartosc wartosc_dokladnosc(double x, double p){
   wartosc przedzial;
   przedzial.x = (x - p*(double)fabsl(x)/100);
   przedzial.y = (x + p*(double)fabsl(x)/100);
   przedzial.czy_anty = 0;
   return przedzial;
}



wartosc wartosc_od_do(double x, double y){
   wartosc przedzial;
      double srednia = (x+y)/2, roznica = (y-x)/2;/*wiemy że y > x*/
      przedzial.x = srednia-roznica;
      przedzial.y = srednia+roznica;
      return przedzial;
}



wartosc wartosc_dokladna(double x){
   wartosc przedzial;
   przedzial.x = x;
   przedzial.y = x;
   przedzial.czy_anty = 0;
   return przedzial;
}



bool in_wartosc(wartosc w, double x){
   bool czy_powinien_byc_na_tym_odcinku;
   if(w.czy_anty == 0){
      czy_powinien_byc_na_tym_odcinku = true;
   }else{
      czy_powinien_byc_na_tym_odcinku = false;
   }
   if( -1*EPSILON < x - w.x && -1*EPSILON < w.y - x){
      return czy_powinien_byc_na_tym_odcinku;
   }else {
      return !czy_powinien_byc_na_tym_odcinku;
   }
}



double min_wartosc(wartosc w){
   if(w.czy_anty == 0){
      return -HUGE_VAL;
   } else {
      return w.x;
   }
}



double max_wartosc(wartosc w){
   if(w.czy_anty == 0){
      return HUGE_VAL;
   } else {
      return w.y;
   }
}



/*double sr_wartosc(wartosc w){
   if(isinf(w.x) && isinf(w.y)){
      return NAN;
   }else if(w.czy_anty == 0){
      return (w.x+w.y)/2;
   } else {
      return 0;//2 anty przedziały inf + -inf = 0;
   }
}*/



wartosc plus(wartosc a, wartosc b);


/*
wartosc minus(wartosc a, wartosc b){//dodajemy -b
   wartosc minus_b;
   minus_b.x = -1*b.y;
   minus_b.y = -1*b.x;
   minus_b.czy_nan = b.czy_nan;
   minus_b.czy_anty = b.czy_anty;
   return plus(a,minus_b);
}*/



wartosc razy(wartosc a, wartosc b);

/*wartosc odwrotnosc(wartosc a){//dzielenie to mnożenie przez zbiór odwróconych wartości zatem tu tworzymy owy zbiór
   wartosc odwrotny;
   //UWAGA nie jestesmy wstanie reprexentowac przedziałów [-inf,a] ani [a,inf] zatem z nimi uporami sie w funkcji podziel.
   if(a.czy_nan == 1 || (a.x == 0 && a.y == 0)){//jeżeli odwracamy 0 lub NAN to mamy NAN
      odwrotny.x = odwrotny.y = NAN;
      odwrotny.czy_nan = 1;   
   }else if({
      
   }
   return odwrotny;
}*/

wartosc podzielic(wartosc a, wartosc b);

void coute(wartosc a){
   printf("%.10lf %.10lf %d %d\n",a.x,a.y,a.czy_anty,a.czy_nan);
}

int main(){
   
   wartosc a_dod, b_dod;
   a_dod.czy_anty = 1;
   b_dod.czy_anty = 0;
   a_dod.czy_nan = 0;
   b_dod.czy_nan = 0;
   a_dod.x = -3.5;
   a_dod.y = 3;
   b_dod.x = 2;
   b_dod.y = 2.5;
   printf("a_dod: ");
   coute(a_dod);
   coute(b_dod);
   
   //printf("%lf",sr_wartosc(a_dod));
   /*printf("[%lf : %lf]",wartosc_dokladnosc(a,b).x,wartosc_dokladnosc(a,b).y);
   a = HUGE_VAL;
   b = NAN;
   c = -HUGE_VAL;
   printf("[%lf : %lf]", fmax(HUGE_VAL,c), fmin(c,a));*/
}