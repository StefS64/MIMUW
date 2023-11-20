#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int maks(int x, int y)
{
  return x > y? x : y;//UWAGA ? to też operator więc dałbym "y ? x"
}

int min(int x, int y)
{
  return x + y - maks(x, y);//UWAGA spoko osobiście bym  zrobił ? ale z maksem też spoko
}

/* Funkcja Skrajnosci zwróci nam wskaźnik na tablicę indeksów,
które to będą wskazywać kolejno na pozycje pierwszej od lewej 
trójki hoteli z parami różnych sieci. Obecność zer na polach wynik[0]
i wynik[1] będzie świadczyła o tym, że w nie ma więcej niż dwóch sieci hoteli. */

long unsigned int *Skrajnosci(int H[], long unsigned int n)
{
  long unsigned int *wynik = malloc(3 * sizeof(long unsigned int));
  wynik[0] = 0;
  wynik[1] = 1;
  wynik[2] = 1;
  while((H[wynik[1]] == H[0]) && (wynik[1] < n))
  {
    wynik[1]++;
  }
  wynik[2] = wynik[1] + 1;
  while((wynik[2] < n) && ((H[wynik[2]] == H[wynik[1]]) || (H[wynik[2]] == H[0])))
  {
    wynik[2]++;
  }
  if(wynik[2] >= n) 
  {
    wynik[1] = 0;
  }
  return wynik;
}

/* Poniższa funkcja dostarcza nam odpowiedź na pierwsze zapytanie. Algorytm
polega na przejściu przez tablicę "gąsienicą", która posiada trzy wskaźniki
(poniżej będą to indeks_1, indeks_2 oraz indeks_3), które będą wskazywać na 
aktualnie rozpatrywane trójki hoteli. Funkcji Skrajnosci użyliśmy, by zacząć
z dobrego miejsca lub stwierdzić, że dana trójka nie istnieje. */

int najmniejsze_maksimum(int H[], int D[], long unsigned int n)//UWAGA czym jest H i D można dać mały kommentarz
{
  long unsigned int *poczatek = Skrajnosci(H, n);
  if((poczatek[0] == 0) && (poczatek[1] == 0))//UWAGA poprawnie alternatywnie możesz: (!poczatek[0] && !poczatek[1]) jest krócej chyba łatwiej się czyta
  {
    return 0;
  }
  long unsigned int indeks_1 = 0, indeks_2 = poczatek[1], indeks_3 = poczatek[2];
  int wynik = maks(D[indeks_2] - D[indeks_1], D[indeks_3] - D[indeks_2]);
  while(1) 
  {
    if(H[indeks_1] == H[indeks_1 + 1])
    {
      indeks_1++;
    }else
    {
      if(H[indeks_2] == H[indeks_2 + 1])
      {
        indeks_2++;
      }else
      {
        indeks_1 = indeks_2;
        indeks_2++;
        while((H[indeks_3] == H[indeks_1]) || (H[indeks_3] == H[indeks_2]))
        {
          indeks_3++;
          if(indeks_3 == n)
          {
            free(poczatek);
            return wynik;
          }
        }
      }
    }
    wynik = min(wynik, maks(D[indeks_2] - D[indeks_1], D[indeks_3] - D[indeks_2]));
  }
}

/* Tu odpowiadamy na drugie zapytanie, korzystając z obserwacji,
że dla danego hotelu B najbardziej opłaca nam się rozpatrywać hotele
A i C, które znajdują się odpowiednio najbardziej na prawo i lewo
na naszej drodze. */

int najwieksze_minimum(int H[], int D[], long unsigned int n)//UWAGA po co unsigned?
{
  int wynik = 0;
  int *zrotowane_H = malloc(n * sizeof(int)); // Tutaj rotujemy tablicę, by sprytnie skorzystać z funkcji Skrajnosci.
  for(long unsigned int i = 0; i < n; i++)
  {
    zrotowane_H[i] = H[n - 1 - i];
  }
  long unsigned int *Lewa = Skrajnosci(H, n);
  long unsigned int *Prawa = Skrajnosci(zrotowane_H, n);
  if((Lewa[0] == 0) && (Lewa[1] == 0))//UWAGA znowu (!Lewa[0] && !Lewa[1])
  {
    free(zrotowane_H);
    free(Lewa);
    free(Prawa);
    return 0;
  }else
  {
    for(long unsigned int j = Lewa[1]; j < n - Prawa[1]; j++)
    {
      for(int k = 0; k < 3; k++)
      {
        if(H[Lewa[k]] != H[j])
        {
          for(int l = 0; l < 3; l++)
          {
            if((H[n - Prawa[l] - 1] != H[j]) && (H[n - Prawa[l] - 1] != H[Lewa[k]]))
            {
              wynik = maks(wynik, min(D[j] - D[Lewa[k]], D[n - Prawa[l] - 1] - D[j]));
            }
          }
        }
      }
    }
    free(zrotowane_H);
    free(Lewa);
    free(Prawa);
    return wynik;
  }
}

int main()
{
  long unsigned int m;
  assert(scanf("%lu", &m) == 1);//UWAGA lepiej zrobić !scanf("%d %d")
  int *hotel = malloc(m * sizeof(int));
  int *dystans = malloc(m * sizeof(int));
  for(long unsigned int i = 0; i < m; i++)
  {
    assert(scanf("%d %d", &hotel[i], &dystans[i]) == 2);//UWAGA lepiej zrobić !scanf("%d %d")
  }
  int rezultat1 = najmniejsze_maksimum(hotel, dystans, m);
  int rezultat2 = najwieksze_minimum(hotel, dystans, m);
  printf("%d %d", rezultat1, rezultat2);//UWAGA tego nwm ja bym włożył te funkcję od razu do printf ale w twój sposób może być czytelniej. Jak uważasz wsm
  free(hotel);
  free(dystans);
}
