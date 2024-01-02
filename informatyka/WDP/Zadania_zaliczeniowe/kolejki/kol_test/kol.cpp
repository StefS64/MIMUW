#include <stdio.h>
#include <vector>
#include <cstdlib>
#include "kol.h"

struct lista{
   interesant *head;
   interesant *tail;
};

/*DEKLARACJA FUNKCJI POMOCNICZYCH*/
/*
stworzenie listy dwóch strażników w kolejce implementacja jak na wykładzie.
każdy strażnik reprezentuje koniec i początek kolejki, niekoniecznie
każdy jest zawsze końcem lub początkiem, mogą się zamieniać.
*/

lista stworz_liste() {
   lista res {
      new interesant,//head
      new interesant //tail
   };
   res.head->a = NULL;
   res.head->b = res.tail;
   res.tail->a = NULL;
   res.tail->b = res.head;
   return res;
}

/*
przełącza wskaźniki aktualnego interesanta z starego na nowy.
*/

void polacz(interesant *akt, interesant *stary, interesant *nowy) {
   if (akt) {
      if(akt->a == stary){
         akt->a = nowy;
      }
      else{
         akt->b = nowy;
      }
   }
}

/*
dodaje na koniec listy "l" interesanta nowy.
*/

void dodaj_na_koniec(lista &l, interesant *nowy){
   nowy->a = l.head;
   nowy->b = l.head->b;
   polacz(l.head->b, l.head, nowy);
   l.head->b = nowy;
}

/*
funkcja bierze dwie listy "l1" i "l2" dołącza całą listę "l1" na koniec "l2".
liste "l1" pozostawia pustą
*/

void scal(lista &l1, lista &l2) {
   interesant *x = l2.head;
   interesant *y = l1.tail;
   polacz(x->b, x, y->b);
   polacz(y->b, y, x->b);
   x->b = y;
   y->b = x;
   l2.head = l1.head;
   l1.tail = y;
   l1.head = x;
}

/*
łączy wskazniki sąsiadów człowieka skutecznie wykluczając go z kolejki.
*/

void usun_interesanta(interesant *czlowiek) {
   polacz(czlowiek->a, czlowiek, czlowiek->b);
   polacz(czlowiek->b, czlowiek, czlowiek->a);
}

/*
znając aktualnego i poprzedniego interesanta od którego przyszliśmy(może być strażnikiem),
zwraca następnego.
*/

interesant *zwroc_interesanta_w_dobrym_kierunku(interesant *akt, interesant *&zeszly){
   if(akt){
      if(akt->a != zeszly){
         zeszly = akt;
         return akt->a;
      }
      else{
         zeszly = akt;
         return akt->b;
      }
   }
   return akt;
}

/*
idzie od aktualnego do stopu, wrzucając odpowiednio interesantów, przez których przechodzi do wektora.
*/

void dodaj_do_momentu(interesant *aktualny, interesant *poprzedni, interesant *stop, std::vector<interesant*> &wyn){
   wyn.push_back(aktualny);
   while(aktualny != stop){
      aktualny = zwroc_interesanta_w_dobrym_kierunku(aktualny, poprzedni);
      wyn.push_back(aktualny);
   }
}

/*
usuwa dowlnych interesantów od człowieka do osoby, wkładając przy tym usuniętych na vector.
idzie od dalszego w kolejce interesanta i szuka w obie strony kolejki pierwszego. Jak znajdzie,
to zaczyna odpowiednio usuwać interesantów od znalezionego "człowieka"(pierwszego) do "osoby".
wiemy, że "człowiek" zawsze stoi przed "osoba" w kolejce.
*/

std::vector<interesant*> usun_interesantow(interesant *czlowiek, interesant *osoba){
   interesant *strona_A = osoba->a, *strona_B = osoba->b, *zeszly_A = osoba, *zeszly_B = osoba;
   std::vector<interesant*> wyn;
   while (zeszly_A != czlowiek && zeszly_B != czlowiek){
      if(strona_A){
         strona_A = zwroc_interesanta_w_dobrym_kierunku(strona_A, zeszly_A);
      }
      if(strona_B){
         strona_B = zwroc_interesanta_w_dobrym_kierunku(strona_B, zeszly_B);
      }
   }
   if(zeszly_A == czlowiek){//
      dodaj_do_momentu(zeszly_A, strona_A, osoba, wyn);
      polacz(strona_A, zeszly_A, osoba->b);
      polacz(osoba->b, osoba, strona_A);
   }
   else{
      dodaj_do_momentu(zeszly_B, strona_B, osoba, wyn);
      polacz(strona_B, zeszly_B, osoba->a);
      polacz(osoba->a, osoba, strona_B);
   }
   return wyn;
}

bool czy_pusta(lista l){
   return l.tail->b == l.head;
}

/*KONIEC FUNKCJI POMOCNICZYCH*/

/*FUNCKJE SPECYFIKACJI BIBLIOTECZKI*/

std::vector<lista> kol;
int numer = 0;

void otwarcie_urzedu(int m){
   for(int i = 0; i < m; i++){
      kol.push_back(stworz_liste());
   }
}

interesant *nowy_interesant(int k){
   interesant *nowy = (interesant*)malloc(sizeof(interesant));
   nowy->liczba = numer++;
   dodaj_na_koniec(kol[k], nowy);
   return nowy;
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
      obsluzono = kol[k].tail->b;
      usun_interesanta(kol[k].tail->b);
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

std::vector<interesant*> fast_track(interesant *i1, interesant *i2){
   return usun_interesantow(i1, i2);
}

void naczelnik(int k){
   zamien(kol[k]);
}

std::vector<interesant*> zamkniecie_urzedu(){
   std::vector<interesant*> wyn;
   for(int i  = 0; i < (int)kol.size(); i++){
      if(!czy_pusta(kol[i])){
         dodaj_do_momentu(kol[i].tail->b, kol[i].tail, kol[i].head->b, wyn);
      }
      delete(kol[i].head);
      delete(kol[i].tail);
   }
   kol.clear();
   return wyn;
}
