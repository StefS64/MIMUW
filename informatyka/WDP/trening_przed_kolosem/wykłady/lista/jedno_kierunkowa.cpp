#include <stdio.h>
#include <cstdlib>
typedef struct elem {
   int val;
   elem *next;
} elem;
typedef elem* lista;

lista push(lista l, int x){
   lista nowy = (lista)malloc(sizeof(elem));
   if(nowy != NULL){
      nowy->val =x;
      nowy->next = l;
   }
   return nowy;
}
lista pop(lista l){
   if(l == NULL){
      return l;
   }
   lista n = l->next;
   free(l);
   return n;
}
lista reverse(lista l){
   lista res = NULL;
   while(l){
      res = push(res, l->val);
      l = pop(l);
   }
   return res;
}
int front(lista l){
   return l->val;
}
void show(lista l){
   lista temp;//= (lista)malloc(sizeof(elem));
   temp = l;
   while(temp != NULL){
      printf("%d\n", temp->val);
      temp = temp->next;
   }printf("\n");
  // free(temp);
}
void zaplacz(lista &a, lista &b){
   elem* temp;
   if(a && b){
      temp = a->next;
      a->next = b->next;
      b->next = temp;
      zaplacz(b->next , a->next);
   }
}
lista splot(lista a_begin, lista b_begin){
   elem* a = a_begin, *b = b_begin; 
   while(a && b){
      elem* tempa = a->next;
      elem* tempb = b->next;
      a->next = b;
      if(tempa){
         b->next = tempa;
      }
      a = tempa;
      b = tempb;
   }
   if(!a_begin){
      return b_begin;
   }
   return a_begin;
}

int main(){
   lista dlug = NULL;
   lista dochod = NULL; 
   for(int i = 0; i < 10; i++){
      dlug = push(dlug, i);
   }
   for(int i = 0; i < 15; i++){
      dochod = push(dochod, -i);
   }
   show(dlug);
   show(dlug);
   reverse(dlug);
   show(dlug);
   show(dochod);
   printf("splot\n");
   show(splot(dochod, dlug));
   show(dlug);
   show(dochod);
   printf("zaplacz\n");
   zaplacz(dlug, dochod);
   show(dlug);
   show(dochod);
}