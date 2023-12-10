//Stefan Świerczewski
//code review robione przez Atanazy Gawrysiak

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
const double EPSILON = 1e-10;
typedef struct {
    double re;//część rzecziwista liczby zepsolonej
    double im;//część urojona liczby zespolonej
}zespo;



typedef struct{
    char typ;// jeden z typów P K Z
    int k;//numer kartki
    zespo X1;//pierwszy pubnkt prostokata lub prostej zgiecia 
    zespo X2;//drugi punkt prostokąta lub prostej zgiecia
    double r;//promien okregu
} kartka;



bool czy_w_okregu(zespo X, zespo O, double r){
    if(sqrt((X.re - O.re) * (X.re - O.re) + (X.im - O.im) * (X.im - O.im)) - r < EPSILON){
        return true;
    }else{
        return false;
    }
}



bool czy_w_prostokacie(zespo X, zespo A, zespo B){
    if( A.re - EPSILON < X.re &&  A.im - EPSILON < X.im && EPSILON + B.re > X.re && EPSILON + B.im > X.im){
        return true;
    }else{
        return false;
    }
}



zespo suma(zespo A, zespo B){//dodaje dwie liczby
    zespo wyn;
    wyn.re = A.re + B.re;
    wyn.im = A.im + B.im; 
    return wyn;
}



zespo iloczyn(zespo A, zespo B){//mnoży dwie liczby
    zespo wyn;
    wyn.re = A.re * B.re - B.im * A.im;
    wyn.im = A.re * B.im + A.im * B.re;
    return wyn;
}



zespo wektor_kierunkowy(zespo A){//zwraca wektor na okregu jednostkowym o tym samym argumencie co A
    double arg = sqrt(A.re * A.re + A.im * A.im);
    A.re = A.re / arg;
    A.im = A.im / arg;
    return A; 
}



zespo przeciwny(zespo A){
    A.re *= -1;
    A.im *= -1;
    return A;
}



zespo sprzezony(zespo A){
    A.im *= -1;
    return A;
}



int stron(zespo X, zespo A, zespo B){//zwraca po ktorej stronie prostej AB jest X
    B = suma(B, przeciwny(A));
    X = suma(X, przeciwny(A));
    double il_wek = X.re * B.im - X.im * B.re;
    if(fabs(il_wek) <= EPSILON){
        return 0;//na prostej
    }else if(il_wek > EPSILON){
        return 1;//po prawej stronie
    }
    else{
        return -1;//po lewej stronie
    }

}



zespo odbicie_wzgledem_prostej(zespo X, zespo A, zespo B){
    B = suma(B, przeciwny(A));//przesuwa przestrzen o wektor przeciwny do A
    X = suma(X, przeciwny(A));
    X = iloczyn(X, wektor_kierunkowy(sprzezony(B)));//obraca przestrzen by vektor B(prosta A-B) była osią OX
    X = sprzezony(X);//odbijamy względem A-B
    X = iloczyn(X, wektor_kierunkowy(B));//odwracamy przekształcenia oprócz odbicia
    X = suma(X, A);
    return X;
}



void input(int n, kartka *T){//wczytuje wejscie
    for(int i = 1; i <= n; i++){
        assert(scanf(" %c", &T[i].typ));
        if(T[i].typ == 'P'){
            assert(scanf("%lf %lf", &T[i].X1.re, &T[i].X1.im));
            assert(scanf("%lf %lf", &T[i].X2.re, &T[i].X2.im));
        }
        else if(T[i].typ == 'K'){
            assert(scanf("%lf %lf %lf", &T[i].X1.re, &T[i].X1.im, &T[i].r));
        }
        else if (T[i].typ == 'Z'){
            assert(scanf("%d %lf %lf", &T[i].k, &T[i].X1.re, &T[i].X1.im));
            assert(scanf("%lf %lf", &T[i].X2.re, &T[i].X2.im));
        }
    }
}



int ile_przebic(int num_k, zespo X,kartka *T){

    if(T[num_k].typ == 'P'){
        if(czy_w_prostokacie(X, T[num_k].X1, T[num_k].X2)){
            return 1;
        }else{
            return 0;
        }
    }else if(T[num_k].typ == 'K'){
        if(czy_w_okregu( X, T[num_k].X1, T[num_k].r)){
            return 1;
        }else{
            return 0;
        }
    }else{
        zespo X_odbit = odbicie_wzgledem_prostej(X, T[num_k].X1, T[num_k].X2);
        if(stron(X, T[num_k].X1, T[num_k].X2) == 1){// jeżeli jest po prawej prostej to go nie liczymy
            return 0;
        }else{
            if(czy_w_okregu(X, X_odbit, EPSILON)){//sprawdza czy X i X_odbit są tym samym punktem
                return ile_przebic(T[num_k].k, X, T);
            }else{
                return ile_przebic(T[num_k].k, X, T) + ile_przebic(T[num_k].k, X_odbit, T);
            }
        }
    }
}



int main(){
    int n, zapytania;
    assert(scanf("%d %d", &n, &zapytania));
    kartka *T = malloc(sizeof(kartka) * (size_t)(n+1));
    input(n, T);
    zespo X;
    int k;
    for(int i = 0; i < zapytania; i++){
        assert(scanf("%d %lf %lf", &k, &X.re, &X.im));
        printf("%d\n", ile_przebic(k, X, T));
    }
}