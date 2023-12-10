#include <stdio.h>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;
int walka(int a, int b){
   if(a == b){
      return a-1;
   }else{
      return a+b-1;
   }
}
void choose_next(int &aktual, queue<int> &kol_fighters,queue <int> &kol){
   if(!kol.empty() && !kol_fighters.empty()){
      if(kol.front() <= kol_fighters.front()){
         aktual = kol.front();
         kol.pop();
      }else{
         aktual = kol_fighters.front();
         kol_fighters.pop();
      }
   }else if(!kol.empty()){
      aktual = kol.front();
      kol.pop();
   }else if(!kol_fighters.empty()){
      aktual = kol_fighters.front();
      kol_fighters.pop();
   }
}





int robakolak(const vector <int> r){

   queue<int> kol;
   for(int i = 0; i < r.size(); i++){
      kol.push(r[i]);
   }
   queue<int> kol_fighters;
   int aktual = r[0];
   int oponent;
   while(!kol.empty() || !kol_fighters.empty()){
      if(!kol_fighters.empty() && !kol.empty()){
         oponent = choose_next(oponent, kol_fighters, kol);
         kol_fighters.push(walka(oponent, aktual));
      }else if(!kol.empty()){
         if(kol.front() == aktual){
            kol.pop();
            aktual--;
         } else{
            kol_fighters.push(walka(kol.front(), aktual));
            kol.pop();
            choose_next(aktual, kol_fighters, kol);
         }
      }else{
         if(kol_fighters.front() == aktual){
            kol_fighters.pop();
            aktual--;
         } else{
            kol_fighters.push(walka(kol_fighters.front(), aktual));
            kol_fighters.pop();
            choose_next(aktual, kol_fighters, kol_fighters);
         }
      }
   }
   return aktual;
}


int main(){

}