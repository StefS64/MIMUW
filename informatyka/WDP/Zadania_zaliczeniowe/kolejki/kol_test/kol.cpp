#include <stdio.h>
#include <vector>
#include <cstdlib>
#include "kol.h"
#include <iostream>
using namespace std;

typedef struct lista{
   interesant *head;
   interesant *tail;
} lista;

vector<lista> kol;
int numer = 0;
lista stworz_liste() {//stworzenie listy dwie atrapy jedna na początek jedna na koniec
   lista res = {
      .head = (interesant*)malloc(sizeof(interesant)),
      .tail = (interesant*)malloc(sizeof(interesant))
   };
   res.head->A = NULL;
   res.head->B = res.tail;
   res.tail->A = NULL;
   res.tail->B = res.head;
   return res;
}

/*DEKLARACJA WŁASNYCH FUNKCJI*/

bool czy_pusta(lista l){
   return l.tail->B == l.head;
}

void polacz(interesant *&akt, interesant *&stary, interesant *&nowy) {//przelacza wskazniki aktualnego z starego wskaznika na nowy
   if (akt) {
      if(akt->A == stary){
         akt->A = nowy;
      }
      else{
         akt->B = nowy;
      }
   }
}

void otwarcie_urzedu(int m){
   for(int i = 0; i < m; i++){
      kol.push_back(stworz_liste());
   }
}

void dodaj_na_koniec(lista &l, interesant *&nowy){
   nowy->A = l.head;
   nowy->B = l.head->B;
   polacz(l.head->B, l.head, nowy);
   l.head->B = nowy;
}

void scal(lista &l1, lista &l2) {
   interesant *x = l2.head;
   interesant *y = l1.tail;
   polacz(x->B, x, y->B);
   polacz(y->B, y, x->B);
   x->B = y;
   y->B = x;
   l2.head = l1.head;
   l1.tail = y;
   l1.head = x;
}

void usun_interesanta(interesant *czlowiek) {//dlaczego tu bez referencji?
   polacz(czlowiek->A, czlowiek, czlowiek->B);
   polacz(czlowiek->B, czlowiek, czlowiek->A);
}

interesant *nowy_interesant(int k){
   interesant *nowy = (interesant*)malloc(sizeof(interesant));
   nowy->liczba = numer++;
   dodaj_na_koniec(kol[k], nowy);
   return nowy;
}

interesant *nastepny(interesant *akt, interesant *&zeszly){
   if(akt){
      if(akt->A != zeszly){
         zeszly = akt;
         return akt->A;
      }
      else{
         zeszly = akt;
         return akt->B;
      }
   }
   return akt;
}

void show(lista l, int num){
   interesant* print = l.tail->B;
   interesant* zeszly = l.tail;
   cout <<num<<": ";
   while(print != l.head){
      cout <<print->liczba<<" ";
      print = nastepny(print, zeszly);
   }cout<<endl;   
}

void show_kolejki(){
   for(int i  = 0; i < (int)kol.size(); i++){
      show(kol[i], i);
   }
}

void dodaj_do_momentu(interesant *aktualny, interesant *poprzedni, interesant *stop, vector<interesant*> &wyn){
   wyn.push_back(aktualny);
   //cout<<"hello"<<endl;
   while(aktualny != stop){
      
      aktualny = nastepny(aktualny, poprzedni);
      wyn.push_back(aktualny);
   }
}

vector<interesant*> usun_interesantow(interesant *&czlowiek, interesant *&osoba){
   interesant *strona_A = osoba->A, *strona_B = osoba->B, *zeszly_A = osoba, *zeszly_B = osoba;
   vector<interesant*> wyn;
   while (zeszly_A != czlowiek && zeszly_B != czlowiek){
      if(strona_A){
         strona_A = nastepny(strona_A, zeszly_A);
      }
      if(strona_B){
         strona_B = nastepny(strona_B, zeszly_B);
      }
   }
   if(zeszly_A == czlowiek){\
      dodaj_do_momentu(zeszly_A, strona_A, osoba, wyn);
      polacz(strona_A, zeszly_A, osoba->B);
      polacz(osoba->B, osoba, strona_A);
   }
   else{
      dodaj_do_momentu(zeszly_B, strona_B, osoba, wyn);
      polacz(strona_B, zeszly_B, osoba->A);
      polacz(osoba->A, osoba, strona_B);
   }
   return wyn;
}

void zamien(lista &l){
   interesant *tymczas = l.head;
   l.head = l.tail;
   l.tail = tymczas; 
}

int numerek(interesant *i){
   return i->liczba;
}

interesant *obsluz(int k){
   interesant *obsluzono = NULL;
   if(!czy_pusta(kol[k])){
      obsluzono = kol[k].tail->B;
      usun_interesanta(kol[k].tail->B);
   }
   return obsluzono;
}

void zmiana_okienka(interesant *i, int k){
   usun_interesanta(i);
   dodaj_na_koniec(kol[k], i);
}

void zamkniecie_okienka(int k1, int k2){
   scal(kol[k1], kol[k2]);
}
vector<interesant*> fast_track(interesant *i1, interesant *i2){
   return usun_interesantow(i1, i2);
}
void naczelnik(int k){
   zamien(kol[k]);
}
vector<interesant*> zamkniecie_urzedu(){
   vector<interesant*> wyn;
   for(int i  = 0; i < (int)kol.size(); i++){
      if(!czy_pusta(kol[i])){
         dodaj_do_momentu(kol[i].tail->B, kol[i].tail, kol[i].head->B, wyn);
      }
      free(kol[i].head);
      free(kol[i].tail);
   }
   kol.clear();
   return wyn;
}
