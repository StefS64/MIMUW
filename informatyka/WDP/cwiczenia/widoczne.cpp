#include <stdio.h>
#include <cstdlib>
#include <cassert>
#include <stack>
using namespace std;

int main(){
   int n;
   assert(scanf("%d", &n));
   int *T = (int*)malloc(sizeof(int)*n);
   int *wyn = (int*)malloc(sizeof(int)*n);
   for(int i = 0; i < n; i++){
      wyn[i] = 0;
      assert(scanf("%d", &T[i]));
   }
   stack<int> a;
   a.push(T[0]);
   for(int i = 1; i < n; i++){
      while(!a.empty() && a.top() <= T[i]){
         a.pop();
         wyn[i]++;
      }
      if(!a.empty()){
         wyn[i]++;
      }
      //wyn[i]+=a.size();
      a.push(T[i]);
   }
   while (!a.empty()){
      a.pop();
   }
   a.push(T[n-1]);
   for(int i = n-2; i >= 0; i--){
      while(!a.empty() && a.top() <= T[i]){
         a.pop();
         wyn[i]++;
      }
      if(!a.empty()){
         wyn[i]++;
      }
      //wyn[i]+=a.size();
      a.push(T[i]);
   }
   for(int i = 0; i < n; i++){
      printf("%d ", wyn[i]);
   }
   /*for(int i = 0; i < n; i++){
      printf("%d", T[i].val);
   }*/
}