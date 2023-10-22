#include <stdio.h>
#include <stdlib.h>


typedef struct {
   int dl;
   double el[];
}ciag;


ciag *roznica(ciag *c){
   ciag *d = malloc(sizeof(ciag) + (long unsigned int)(c->dl-1)*sizeof(double));
   d->dl = c->dl-1;
   for(int i = 0;i < c->dl-1;i++){
      d->el[i] = c->el[i+1] - c->el[i]; 
   }
   return d;
}


void print_ciag(ciag *c){
   //printf("enter %d", c->dl);
   for(int i = 0; i < (c->dl) ;i++){
      printf("%lf ",c->el[i]);   
   }printf("\n");
   //printf("exit");
}


int main(){
   long unsigned int length;
   
   if(scanf(" %lu", &length) != 1){
      printf("error");
   }

   ciag *c = malloc(sizeof(ciag*)+length*sizeof(double));
   
   c->dl = (int)length;

   for(int i = 0; i < c->dl; i++){
      if(scanf(" %lf", &c->el[i]) != 1){
         printf("error");
      }
   }

   for(int i = 0; i < c->dl ;i++){
      printf("%lf ",c->el[i]);   
   }printf("\n");
   
   print_ciag(roznica(c));
   ciag **d = malloc(sizeof(ciag*)*(long unsigned int)c->dl);
   d[0] = c;
   for(int i = 0; i < c->dl-1;i++){
      d[i+1] = roznica(d[i]);
       print_ciag(d[i+1]);
   }
   for(int i = 0; i < c->dl;i++){
       print_ciag(d[i]);
   }
   free(c);
   free(d);
   //printf(" %.lf", (double)2/3);
}