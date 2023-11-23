//Atanazy Gawrysiak
//code review ze Stefanem Świerczewskim
#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <complex.h>
#include <math.h>

typedef double complex zespkt;
const double EPS = 1e-8;
const double PI = 3.14159265358979323846;

typedef struct kartka
{
    char typ;
    int k;
    double x1, y1, x2, y2, r;
} kartka;

void zamien(double *a, double *b) //zamienia dwa double
{
    double _a = *a;
    double _b = *b;
    *b = _a;
    *a = _b;
}

zespkt odbij(zespkt P, zespkt A, zespkt B) //odbija P wzgledem AB, kod z geeksforgeeks
{
    zespkt Pt = P - A; 
    zespkt Bt = B - A; //przesuniecie punktow tak aby A bylo w (0,0)
    zespkt Pr = Pt / Bt; //obrot tak, zeby AB byl poziomy
    return conj(Pr) * Bt + A; // odbicie wzgledem OX i odwrocenie poprzednich przeksztalcen
}

int strona(zespkt P, zespkt A, zespkt B) //zwraca -1 jak P po lewej stronie AB, 0 jak jest na prostej, 1 jak po prawej
{
    zespkt Pt = P - A;
    zespkt Bt = B - A; //przesuwam punkty tak zeby A wyladowal w (0, 0)
    if(fabs(cimag(Pt)) < EPS && fabs(creal(Pt)) < EPS) //przypadek gdy A = P
        return 0;
    double katP = carg(Pt);
    double katmP = carg(-Pt);
    double katB = carg(Bt);
    double katmB = carg(-Bt);
    if(fabs(katB) < EPS || fabs(katmB) < EPS)
        if(fabs(katP) < EPS || fabs(katmP) < EPS)
            return 0; //przypadek gdy AB to os OX i P lezy na niej, trzeba to ifowac, bo argument pi to to samo, co -pi
    if(fabs(katP - katB) < EPS || fabs(katP - katmB) < EPS) //P jest na AB
        return 0;
    int mn = 1;
    if(katB < 0) //od teraz katB bedzie nieujemny a katmB niedodatni
    {
        mn = -1;
        zamien(&katB, &katmB);
    }
    if(katP > katB || katP < katmB)
        return -mn;
    return mn;
}

double odlkw(double x1, double y1, double x2, double y2) //zwaraca kwadrat odleglosci dwoch punktow
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int licz(kartka tab[], int k, double x, double y) //liczy wynik dla punktu (x, y) w kartce k
{
    if(tab[k].typ == 'K')
        return odlkw(x, y, tab[k].x1, tab[k].y1) < (tab[k].r * tab[k].r + EPS);
    if(tab[k].typ == 'P')
    {
        if(x > tab[k].x1 - EPS && x < tab[k].x2 + EPS && y > tab[k].y1 - EPS && y < tab[k].y2 + EPS)
            return 1;
        return 0;
    }
    zespkt P = x + y * I;
    zespkt A = tab[k].x1 + tab[k].y1 * I;
    zespkt B = tab[k].x2 + tab[k].y2 * I;
    zespkt Pp = odbij(P, A, B);
    int str = strona(P, A, B);
    if(str == 1)
        return 0;
    if(str == 0)
        return licz(tab, tab[k].k, x, y);
    return licz(tab, tab[k].k, x, y) + licz(tab, tab[k].k, creal(Pp), cimag(Pp));
}

int main()
{
    /*zespkt P = 0.0 + -0.3 * I;
    zespkt A = 0.0 + 0.0 * I;
    zespkt B = 30.0 + 0.0 * I; 
    zespkt Pp = odbij(P, A, B);
    printf("%lf %lf %d", creal(Pp), cimag(Pp), strona(P, A, B));*/
    int n, q;
    assert(scanf("%d%d", &n, &q) == 2);
    kartka *tab = malloc(sizeof(kartka) * (size_t)(n + 9));
    for(int i = 1; i <= n; i++) //wczytywanie wejscia
    {
        kartka nowa;
        assert(scanf(" %c", &nowa.typ) == 1);
        if(nowa.typ == 'P')
            assert(scanf("%lf%lf%lf%lf", &nowa.x1, &nowa.y1, &nowa.x2, &nowa.y2) == 4);
        if(nowa.typ == 'K')
            assert(scanf("%lf%lf%lf", &nowa.x1, &nowa.y1, &nowa.r) == 3);
        if(nowa.typ == 'Z')
            assert(scanf("%d%lf%lf%lf%lf", &nowa.k, &nowa.x1, &nowa.y1, &nowa.x2, &nowa.y2) == 5);
        tab[i] = nowa;
    }
    while(q--)
    {
        int k;
        double x, y;
        assert(scanf("%d%lf%lf", &k, &x, &y) == 3);
        printf("%d\n", licz(tab, k, x, y));
    }
}