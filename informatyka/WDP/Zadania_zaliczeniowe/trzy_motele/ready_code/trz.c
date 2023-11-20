#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int left_close;//pierwszy motel z innej sieci
    int left_close_different;//pierwszy taki motel którego sieć jest różna od rozpatrzanego oraz zdefiniowanego powyżej
    int right_close;
    int right_close_different;
}closest_motel;


//structura trzymająca odległość motelu oraz jego sieć
typedef struct{
    int chain; 
    int distance;
}motel;


//deklaracja zmiennych globalnych
int Left[3] = {0, -1, -1};//wystarczy mieć po 3 motele z różnych śieci od lewej i od prawej strony tablicy.
int Right[3] = {0, -1, -1};
motel m_position[1000000];//siec oraz odleglosc od poczatku motela
closest_motel T[1000000];
int size;//ilość moteli/wielkość tablicy



int max(int A, int B){
    return A > B ? A : B;
}



int min(int A, int B){
    return A > B ? B : A;
}



void input(){
    for(int i = 0; i < size; i++){
        if(!scanf("%d %d", &m_position[i].chain, &m_position[i].distance))printf("WRONG INPUT");
    }
}



void set_minus_one(int num){
    T[num].left_close = -1;
    T[num].left_close_different = -1;
}

/*
znajduje 3 pierwsze hotele z lewej strony które należą do 3 różnych sieci
*/

void pre_proces_max_left(){
    int count = 1;
    int i = 1;
    while(i < size && count < 2){
        if(m_position[i].chain != m_position[0].chain){
            Left[1] = i;
            count++;
        }
        i++;
    }
    while(i < size && count < 3){
        if(m_position[i].chain != m_position[0].chain && m_position[Left[1]].chain != m_position[i].chain){
            Left[2] = i;
            count++;
        }
        i++;
    }
}

/*
preprocessing tablicy T lewych indeksów, pierwszych dwóch taki moteli, że pierwszy jest
najbliższym z innej sieci, z lewej strony. A następny jest najbliższy motel z innej sieci,
niż rozpatrzany oraz znaleziony najbliższy.
*/

void pre_proces_min_left(){
    set_minus_one(0);
    for(int i = 1; i < size; i++){
        if(m_position[i-1].chain != m_position[i].chain){//motel o jeden wcześniej jest z innej sieci, jest najbliższym z innej sieci
            T[i].left_close = i-1;
            if(T[i-1].left_close == -1){//jeżeli nie istnieje pierwszy różny od lewego
                T[i].left_close_different = -1;
            }
            else if(m_position[T[i-1].left_close].chain != m_position[i].chain){//jeżel są z różnych sieci
                T[i].left_close_different = T[i-1].left_close;
            }else{//jeżeli są z tej samej sieci to dalszy będzie tym samym dalszym dla aktuanlnie rozpatrzany
                T[i].left_close_different = T[i-1].left_close_different;
            }
        }else{//lewy sąsiad jest z tej samej sieci, więc ma te same najbliższe motele
            T[i].left_close = T[i-1].left_close;
            T[i].left_close_different = T[i-1].left_close_different;
        }
    }
}



void swap(motel *A, motel *B){
    motel temp = *A;
    *A = *B;
    *B = temp;
}

/*
funkcje do preprocesingu prawego:
*/

/*
funkcja odwracająca tablicę pozycji oraz sieci
*/

void reverse_m_postion(){
    for(int i = 0; i < size/2; i ++){
        swap(&m_position[i], &m_position[size-i-1]);
    }
}

/*
funkcja po obróceniu tablicy oblicza prawy pre-procesing i wpisuje wyniki na odpowiednie pozycje
*/

void pre_proces_min_right(){
    pre_proces_min_left();
    for(int i = 0; i < size; i ++){
        T[i].right_close = T[size-i-1].left_close;
        T[i].right_close_different = T[size-i-1].left_close_different;
    }
}

/*
oblicza dla obróconej i przepisuje do odpowidniej tablicy
*/

void pre_proces_max_right(){
    pre_proces_max_left();
    for(int i = 0; i < 3; i++){
        Right[i] = Left[i];
    }
}



void pre_proces_right(){
    reverse_m_postion();
    pre_proces_max_right();
    pre_proces_min_right();
    reverse_m_postion();
}



int seperation(int A, int B){
    return abs(m_position[A].distance - m_position[B].distance);
}

/*
odczytuje odleglosc maxymalną odległość A-B lub B-C gdzie B jest środkowym motelem
*/

int find_max_of_closest_values_for_motel(int index){
    if(T[index].left_close == -1 || T[index].right_close == -1){//czy mają najbliższe motele z obu stron
        return INT_MAX;
    } 
    else if(m_position[T[index].left_close].chain != m_position[size-1-T[index].right_close].chain){//czy mają najbliższy motel z różnej sieci z obu stron
        return max(seperation(T[index].left_close, index), seperation(size-1-T[index].right_close, index));
    }
    else if(T[index].left_close_different == -1 && T[index].right_close_different == -1){//czy chociaż jeden najbliższy różny od najbliższych z odpowiednio lewej i prawej strony istnieją
        return INT_MAX;
    }
    else{
        int Max = -1;
        if(T[index].left_close_different != -1){//sprawdza który z dalszych różnych istnieje i następnie oblicza maksymalną odległość miedzy motelam A i B oraz B i C
            Max = max(Max, max(seperation(T[index].left_close_different, index), seperation(size-1-T[index].right_close, index)));
        }
        if(T[index].right_close_different != -1){
            Max = max(Max, max(seperation(T[index].left_close, index), seperation(size-1-T[index].right_close_different, index)));
        }
        return Max;//nigdy nie wyrzuci wartości -1 jest to wartość kontrolna
    }
}

/*
sprawdza czy trójka moteli o indexach w kolejności L, index, R spełnia warunki by odczytać odległość
*/

bool check_if_ok(int L, int index, int R){
    #define diffchain(a, b) (m_position[a].chain != m_position[b].chain)
    if(L == -1 || R == -1){
        return 0;
    }
    else if(m_position[L].distance > m_position[index].distance || m_position[size-1-R].distance < m_position[index].distance){//sprawdza czy są w dobrej kolejności
        return 0;
    }
    else if(diffchain(L, size-1-R) && diffchain(index, size-1-R) && diffchain(index, L)){//sprawdza czy są z różnych sieci
        return 1;
    }
    return 0;
    #undef diffchain
}

/*
znajduje maximum z trójki najbardziej oddalonych moteli przechodzac po wszystkich kombinacjach tablic Right oraz Left
*/

int find_min_of_furthest_values_for_motel(int index){
    int Max = -1;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(check_if_ok(Left[i], index, Right[j])){
                Max = max(Max, min(seperation(Left[i], index), seperation(size-1-Right[j], index)));
            }
        }
    }
    return Max;
}



void answer(){
    int ansmin = INT_MAX;
    int ansmax = -1;
    for(int i = 0; i < size; i++){
        ansmin = min(ansmin, find_max_of_closest_values_for_motel(i));
        ansmax = max(ansmax, find_min_of_furthest_values_for_motel(i));
    }
    if(ansmax == -1 && ansmin == INT_MAX){
        printf("0 0\n");
    }
    else{
       printf("%d %d", ansmin, ansmax);
    }

}


/*
funkcje sprawdzające do debugowania
*/

void cout_input(){
    for(int i = 0; i < size; i++){
        printf("%d %d\n", m_position[i].chain, m_position[i].distance);
    }
    printf("end of cout_input\n");
    printf("\n");
}



void cout_closest(closest_motel A){
    printf("%d %d %d %d\n", A.left_close_different, A.left_close, A.right_close, A.right_close_different);
}



void cout_T(){
    for(int i = 0; i < size; i++){
        cout_closest(T[i]); 
    }printf("\n");
}



int main(){
    if(!scanf("%d", &size))printf("WRONG INPUT");
    input();
    pre_proces_right();
    pre_proces_min_left();
    pre_proces_max_left();
    answer();
}