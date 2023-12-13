#include <stdio.h>
#include <vector>
#include <cstdlib>
//#include "kol.h"

using namespace std;

struct interesant {
    // Twój kod zaczyna się tu
    interesant *A;
    interesant *B;
    int liczba;
    // A kończy tu
};
typedef struct lista{
   interesant *head;
   interesant *tail;
} lista;

vector<lista> kol;
int numer = 0;
lista create_list() {
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

bool isempty(lista l){
   return l.head->B == l.tail;
}
void polacz(interesant *akt, interesant *stary, interesant *nowy) {
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
      kol.push_back(create_list());
   }
}

void dodaj_na_koniec(lista l, interesant *&nowy){
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

interesant *nowy_interesant(int k){
   interesant *nowy = (interesant*)malloc(sizeof(interesant));
   nowy->liczba = numer++;
   dodaj_na_koniec(kol[k], nowy);
   return nowy;
}

void usun_interesanta(interesant *&czlowiek) {
   polacz(czlowiek->A, czlowiek, czlowiek->B);
   polacz(czlowiek->B, czlowiek, czlowiek->A);
   czlowiek->A = NULL;
   czlowiek->B = NULL;
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

void dodaj_do_momentu(interesant *start, interesant *poprzedni, interesant *stop, vector<interesant*> &wyn){
   do{
      wyn.push_back(start);
      start = nastepny(start, poprzedni);
   }while(start != stop);
}

vector<interesant*> usun_interesantow(interesant *czlowiek, interesant *osoba){
   interesant *strona_A = osoba->A, *strona_B = osoba->B, *zeszly_A = osoba, *zeszly_B = osoba;
   vector<interesant*> wyn;
   do{
      if(strona_A){
         strona_A = nastepny(strona_A, zeszly_A);
      }
      if(strona_B){
         strona_B = nastepny(strona_B, zeszly_B);
      }
   }while (zeszly_A != czlowiek || zeszly_B != czlowiek);
   if(zeszly_A == czlowiek){
      dodaj_do_momentu(zeszly_A, strona_A, osoba, wyn);
      polacz(strona_A, zeszly_A, osoba->B);
      polacz(osoba->B, osoba, strona_A);
   }
   else{
      dodaj_do_momentu(zeszly_B, strona_B, osoba, wyn);
      polacz(strona_B, zeszly_B, osoba->A);
      polacz(osoba->A, osoba, strona_B);
   }
   /*if(zeszly_A == czlowiek){
      polacz(strona_A, zeszly_A, osoba->B);
      polacz(osoba->B, osoba, strona_A);
   }else{
      polacz(strona_B, zeszly_B, osoba->A);
      polacz(osoba->A, osoba, strona_B);
   }*/
   return wyn;
}
void zamien(lista l){
   interesant *tymczas = l.head;
   l.head = l.tail;
   l.tail = tymczas; 
}

int numerek(interesant* i){
   return i->liczba;
}

interesant *obsluz(int k){
   interesant *obsluzono = NULL;
   if(isempty(kol[k])){
      obsluzono = kol[k].tail->A;
      usun_interesanta(kol[k].tail->A);
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
   vector<interesant*> wynik;
   return usun_interesantow(i1, i2);
}
void naczelnik(int k){
   zamien(kol[k]);
}
vector<interesant*> zamkniecie_urzedu(){
   vector<interesant*> wyn;
   for(int i  = 0; i < (int)kol.size(); i++){
      dodaj_do_momentu(kol[i].tail->B, kol[i].tail, kol[i].head, wyn);
      free(kol[i].head);
      free(kol[i].tail);
      //xfree(kol[i]);
   }
   return wyn;
}
//interesant *nowy_interesant(int k)
//interesant *obsluz(int k) 
//void zmiana_okienka(interesant *i, int k) 
//void zamkniecie_okienka(int k1, int k2) 
//vector<interesant*> fast_track(interesant *i1, interesant *i2)
//void naczelnik(int k)
//vector<interesant *> zamkniecie_urzedu()
