#include <stdlib.h>
#include "kol.h"

using namespace std;

// PONIŻSZA IMPLEMENTACJA JEST WZOROWANA NA IMPLEMENTACJI LISTY DWUKIERUNKOWEJ POKAZANEJ NA WYKŁADZIE

typedef struct lista
{
    interesant *glowa, *ogon; // lista to wskaźnik na ogon i głowę, ogon i głowa NIE są elementami listy, tylko strażnikami
} lista;

lista utworz_liste()
{
    interesant *glowa = (interesant *)malloc(sizeof(interesant));
    interesant *ogon = (interesant *)malloc(sizeof(interesant));
    glowa->el1 = NULL;
    glowa->el2 = ogon; // docelowo głowa->l2 wskazuje na pierwszego intereanta, dla pustej listy wskazuje na ogon
    ogon->el1 = NULL;
    ogon->el2 = glowa; // docelowo ogon->l2 wskazuje na ostatniego interesanta, dla pustej listy wskazuje na głowę
    return {glowa, ogon};
}

void zwolnij_liste(lista &l) // funkcja zwalnia pamięć po głowie i ogonie listy (strażnikach), ale nie zwalnia interesantów (to robi użytkownik)
{
    free(l.glowa);
    free(l.ogon);
}

bool czy_pusta_lista(lista &l)
{
    return l.glowa->el2 == l.ogon; // jeśli głowa wskazuje na ogon, to lista jest pusta
}

void link(interesant *el, interesant *old, interesant *nw) // zerwanie połączenia elementu listy el z old i połączenie go z nw
{
    if (el)
    {
        if (el->el2 == old) // sprawdzamy "z której strony" elementu el jest element old i zamieniamy go na nw
        {
            el->el2 = nw;
        }
        else
        {
            el->el1 = nw;
        }
    }
}

void dodaj_na_tyl(lista &l, interesant *i) // wstawia na koniec listy l interesanta i
{
    i->el1 = l.ogon;      // wstawiamy interesanta między ogon listy (strażnika)
    i->el2 = l.ogon->el2; // a jej faktyczny ostatni element
    link(l.ogon->el2, l.ogon, i);
    link(l.ogon, l.ogon->el2, i);
}

void odwroc(lista &l)
{
    interesant *temp = l.glowa;
    l.glowa = l.ogon;
    l.ogon = temp;
}

void usun_interesanta(interesant *el) // usuwa element el (ale nie zwalnia pamięci) i "zaszywa" po nim dziurę w liście
{
    link(el->el1, el, el->el2);
    link(el->el2, el, el->el1);
}

interesant *usun_pierwszy(lista &l) // usuwa pierwszy element listy l i zwraca wskaźnik na niego lub NULL, jeśli lista była pusta
{
    if (czy_pusta_lista(l))
    {
        return NULL;
    }
    interesant *pom = l.glowa->el2;
    usun_interesanta(pom);
    return pom;
}

void polacz_listy(lista &lis1, lista &lis2) // podpina listę lis2 do lis1, a z lis2 robi pustą listę
{
    interesant *b = lis1.ogon;
    interesant *f = lis2.glowa;
    link(b->el2, b, f->el2);
    link(f->el2, f, b->el2);
    b->el2 = f; // z ogona i głowy robimy pustą listę
    f->el2 = b;
    lis1.ogon = lis2.ogon;
    lis2.ogon = b;
}

/* POCZĄTEK DEFINICJI FUNKCJI Z ZADANIA */

lista *okienka = NULL;
int ile_okienek = 0;
int ile_interesantow = 0; // równoważnie: ile numerków zostało wydanych

void otwarcie_urzedu(int m)
{
    ile_okienek = m;
    okienka = (lista *)malloc(ile_okienek * sizeof(lista));
    for (int i = 0; i < m; i++)
    {
        okienka[i] = utworz_liste(); // tworzymy m pustych list (okienek urzędu)
    }
}

interesant *nowy_interesant(int k)
{
    interesant *nowy = (interesant *)malloc(sizeof(interesant));
    nowy->numer = ile_interesantow++; // dajemy nowemu numerek i zwiększamy liczbę wydanych numerków
    dodaj_na_tyl(okienka[k], nowy);
    return nowy;
}

int numerek(interesant *i)
{
    return i->numer;
}

interesant *obsluz(int k)
{
    return usun_pierwszy(okienka[k]);
}

void zmiana_okienka(interesant *i, int k)
{
    usun_interesanta(i);         // usuwa i z jego kolejki
    dodaj_na_tyl(okienka[k], i); // i dodaje go na koniec kolejki o numerze k
}

void zamkniecie_okienka(int k1, int k2)
{
    polacz_listy(okienka[k2], okienka[k1]); // listę okienka o numerze k1 dołączamy do listy okienka o numerze k2, a okienka[k1] staje się pustą listą
}

// założenie: ostatni == aktualny->el1 || ostatni == aktualny->el2
void kroczek(interesant *&aktualny, interesant *&ostatni) // funkcja, która przesuwa wskaźniki aktualny i ostatni w stronę wskaźnika aktualny
{
    if (aktualny)
    {
        if (aktualny->el1 == ostatni)
        {
            ostatni = aktualny;
            aktualny = aktualny->el2;
        }
        else
        {
            ostatni = aktualny;
            aktualny = aktualny->el1;
        }
    }
}

vector<interesant *> fast_track(interesant *i1, interesant *i2)
{
    if (i1 == i2)
    {
        usun_interesanta(i1);
        return {i1};
    }

    // W liście nie określamy kierunku dowiązań, więc żeby znaleźć połączenie między i1 a i2 musimy, idąc od i1, "rozszerzać" się w obie strony naraz. Dlatego
    // bęzdziemy trzymali dwa wektory potencjalnych wyników. Jeśli znajdziemy i2 albo dojdziemy do NULL to wybierzemy właściwy "kierunek" rozszerzania.
    vector<interesant *> wyn1 = {i1}; // idziemy od interesanta i1 w kierunku el1
    vector<interesant *> wyn2 = {i1}; // idziemy od interesanta i2 w kierunku el2
    interesant *ost1 = i1;            // ostatni interesanci, krórych rozpatrywaliśmy
    interesant *ost2 = i1;
    interesant *akt1 = i1->el1; // aktualnie rozpatrywany interesant
    interesant *akt2 = i1->el2;
    bool dobry_kierunek = 0;                                         // 0 jeśli pierwszy krok powinniśmy wykonać w kierunku i1->el1, 1 jeśli w kierunku i1->el2
    while (akt1 && akt2 && akt1 != i2 && akt2 != i2) // wychodzimy z pętli gdy dojdziemy jednym wskaźnikiem do końca listy albo spotkamy i2
    {
        wyn1.push_back(akt1);
        wyn2.push_back(akt2);
        // oboma wskaźnikami idziemy tam, gdzie jeszcze nie byliśmy
        kroczek(akt1, ost1);
        kroczek(akt2, ost2);
    }
    dobry_kierunek = (!akt1 || akt2 == i2) ? 1 : 0; // jeśli akt1 to NULL albo akt2 to i2, to pierwszy dobry krok był w kierunku i1->el2, więc ustawiamy na 1, w p.p. 0

    if (!dobry_kierunek)                            // pierwszy dobry krok był w kierunku i1->el1
    {
        while (ost1 != i2) // idziemy o jeden dalej, żeby wiedzieć który element listy musimy "zszyć" z i1->el2
        {
            wyn1.push_back(akt1);
            kroczek(akt1, ost1);
        }
        link(i1->el2, i1, akt1);
        link(akt1, i2, i1->el2);
        return wyn1;
    }

    // dobry_kierunek == 1, czyli pierwszy dobry krok był w kierunku i1->el2
    while (ost2 != i2) // idziemy o jeden dalej, żeby wiedzieć który element listy musimy "zszyć" z i1->el1
    {
        wyn2.push_back(akt2);
        kroczek(akt2, ost2);
    }
    link(i1->el1, i1, akt2);
    link(akt2, i2, i1->el1);
    return wyn2;
}

void naczelnik(int k)
{
    odwroc(okienka[k]);
}

vector<interesant *> zamkniecie_urzedu()
{
    vector<interesant *> wyn;
    lista pom;
    interesant *akt;
    interesant *ost;
    for (int i = 0; i < ile_okienek; i++) // dla kazdego okienka wypisujemy osoby, które w nim stoją
    {
        pom = okienka[i];
        akt = (pom.glowa)->el2; // aktualnie rozpatrywany interesant
        ost = pom.glowa;        // poprzednio rozpatrzony interesant
        while (akt != pom.ogon) // przechodzimy przez całą listę
        {
            wyn.push_back(akt);
            kroczek(akt, ost); // idziemy tam, gdzie jeszcze nie byliśmy
        }
        zwolnij_liste(okienka[i]); // zwalniamy pamięć po głowie i ogonie listy
    }
    free(okienka);
    return wyn;
}
