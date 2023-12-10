#include <stdio.h>
#include <cstdlib>
typedef struct elem{
   int val;
   elem *next;
   elem *prev;
}elem;
typedef struct lista{
   elem *head;
   elem *tail;
} lista;
lista create_list(){
   lista res = {
      .head = NULL,
      .tail = NULL
   };
   return res;
}
bool isempty(const lista l) {
   return l.head == NULL;
}
void push_front(lista &l, int x){
   elem *nowy = (elem* )malloc(sizeof(elem));
   nowy->next = NULL;
   nowy->prev = l.head;
   nowy->val = x;
   if(!isempty(l)){
      l.head->next = nowy;
   }else{
      l.tail = nowy;
   }
   l.head = nowy;
}
void push_back(lista &l, int x){
   elem *nowy = (elem*)malloc(sizeof(elem));
   nowy->prev = NULL;
   nowy->next = l.tail;
   nowy->val = x;
   if(!isempty(l)){
      l.tail->prev = nowy;
   }else{
      l.head = nowy;
   }
   l.tail = nowy;
}
void pop_front(lista &l){
   if(!isempty(l)){
      elem *el = l.head;
      l.head = l.head->prev;
      if(l.head){
         l.head->next = NULL;
      } else{
         l.tail = NULL;
      }
      free(el);
   }
}
void pop_back(lista &l){
   if(!isempty(l)){
      elem *el = l.tail;
      l.tail = l.tail->next;
      if(l.tail){
         l.tail->prev = NULL;
      } else{
         l.head = NULL;
      }
      free(el);
   }
}
int front(const lista l){
   return l.head->val;
}
int back(const lista l){
   return l.tail->val;
}
void show(lista l){
   elem *temp = l.tail;
   while(temp != NULL){
      printf("%d\n", temp->val);
      temp = temp->next;
   }printf("\n");
}
int main(){
   lista l = create_list();
   push_front(l, 1);
   push_front(l, 2);
   push_front(l, 3);
   push_back(l, 3);
   show(l);
   pop_front(l);
   push_front(l, 2);
   push_front(l, 3);
   push_back(l, 3);
   show(l);
}

