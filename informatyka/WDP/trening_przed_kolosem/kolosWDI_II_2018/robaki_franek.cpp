#include <iostream>
#include <limits.h>
#include <queue>
using namespace std;

int robakolak(const vector<int> &v)
{
    if (v.size() == 1)
    {
        return v[0];
    }
    queue<int> przed_walkami;    // kolejka robali przed walkami, za każdym razem gdy będą walczyć usuwamy z tej kolejki i dodajemy na drugą
    queue<int> po_walkach;       // skoro robale są posortowane, to na tej koelejce też będą w kolejności rosnącej

    for (int i : v)
    {
        przed_walkami.push(i);
    }
    
    int rob1 = przed_walkami.front();
    przed_walkami.pop();
    int rob2 = przed_walkami.front();
    przed_walkami.pop();
    if (rob1 == rob2)
    {
        po_walkach.push(rob1 - 1);
    }
    else
    {
        po_walkach.push(rob1 + rob2 - 1);
    }

    przed_walkami.push(INT_MAX); // atrapa na końcu kolejki

    if (przed_walkami.size() == 1)
    {
        return po_walkach.front();
    }

    while (przed_walkami.size() > 1 && po_walkach.size() == 1 && po_walkach.front() <= przed_walkami.front())
    {   
        int nowy = po_walkach.front() == przed_walkami.front() ? po_walkach.front() - 1 : przed_walkami.front() + po_walkach.front() - 1;
        po_walkach.pop();
        przed_walkami.pop();
        po_walkach.push(nowy);
    }

    while (przed_walkami.size() > 1)
    {
        int r1 = przed_walkami.front();
        int r2 = po_walkach.front();
        int r3;
        if (r1 == r2)
        {
            po_walkach.front()--;
            przed_walkami.pop();
        }
        else if (r1 < r2)
        {
            przed_walkami.pop();
            r3 = przed_walkami.front();
            if (r3 == r2)
            {
                przed_walkami.pop();
                po_walkach.front()--;
            }
            if (r3 < r2)
            {
                przed_walkami.pop();
                po_walkach.push(r3 + r1 - 1);
            }
            if (r3 > r2)
            {
                po_walkach.pop();
                po_walkach.push(r3 + r2 - 1);
            }
        }
        else if (r1 > r2)
        {
            po_walkach.pop();
            r3 = po_walkach.front();
            if (r3 == r2)
            {
                przed_walkami.pop();
                po_walkach.front()--;
            }
            if (r3 < r2)
            {
                po_walkach.pop();
                po_walkach.push(r3 + r2 - 1);
            }
            if (r3 > r2)
            {
                przed_walkami.pop();
                po_walkach.push(r3 + r1 - 1);
            }
        }
    }

    while(po_walkach.size() > 1)
    {
        int pom = po_walkach.front();
        po_walkach.pop();
        int pom2 = po_walkach.front();
        po_walkach.pop();
        int nowy = pom == pom2 ? pom -1 : pom + pom2 - 1;
        po_walkach.push(nowy);
    }
    return po_walkach.front();
}

int robakolak2(const vector<int> &v)
{
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i : v)
    {
        pq.push(i);
    }
    while (pq.size() > 1)
    {
        int pom = pq.top();
        pq.pop();
        int pom2 = pq.top();
        pq.pop();
        int nowy = pom == pom2 ? pom -1 : pom + pom2 - 1;
        pq.push(nowy);
    }
    return pq.top();
}
int walka(int a, int b){
   if(a == b){
      return a-1;
   }else{
      return a+b-1;
   }
}



void choose_next(int &aktual, queue<int> &kol_fighters,queue <int> &kol){
   if(!kol.empty() && !kol_fighters.empty()){
      //cout <<"tutaj"<<endl;
      if(kol.front() <= kol_fighters.front()){
         aktual = kol.front();
        // cout <<aktual<<"hheja"<<endl;
         kol.pop();
      }else{
         aktual = kol_fighters.front();
         //cout <<aktual<<endl;
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





int robakolak_stef(const vector <int> &v){

   queue<int> kol;
   for(int i : v){
      kol.push(i);
   }
   queue<int> kol_fighters;
   int aktual = kol.front();
   //cout<<kol.front()<<" "<<v[0]<<"test"<<endl;
   kol.pop();
   int oponent;
   //cout << aktual <<endl;
   while(!kol.empty() || !kol_fighters.empty()){
      if(!kol_fighters.empty() && !kol.empty()){
         choose_next(oponent, kol_fighters, kol);
         kol_fighters.push(walka(oponent, aktual));
         choose_next(aktual, kol_fighters, kol);
      }else if(!kol.empty()){
         if(kol.front() == aktual){
            kol.pop();
            aktual--;
         } else{
            //cout<<kol.front()<<"test"<<endl;
            kol_fighters.push(walka(kol.front(), aktual));
            kol.pop();
            choose_next(aktual, kol_fighters, kol);
            //cout <<"halo"<<endl;
         }
      }else{
         if(kol_fighters.front() == aktual){
            kol_fighters.pop();
            aktual--;
         } else{
            kol_fighters.push(walka(kol_fighters.front(), aktual));
            kol_fighters.pop();
            choose_next(aktual, kol_fighters, kol);
         }
      }
      //cout << aktual <<endl;
   }
   return aktual;
}
int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (int &i : v)
    {
        cin >> i;
    }
    cout << robakolak(v) << " " <<  robakolak2(v) << " " << robakolak_stef(v)<<'\n';
}