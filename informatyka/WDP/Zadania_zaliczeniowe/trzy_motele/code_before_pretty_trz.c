#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

enum left_or_right {left, right};
typedef struct {
    int left_close;
    int right_close;
    int left_close_different;
    int right_close_different;
}closest_motel;



typedef struct{
    int chain; 
    int distance;
}motel;



int Left[3] = {0, -1, -1};//wystarczy mieć po 3 motele z różnych śieci od lewej i od prawej strony tablicy.
int Right[3]= {0, -1, -1};
motel m_position[1000000];
closest_motel T[1000000];
int size;



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



void cout_input(){
    for(int i = 0; i < size; i++){
        printf("%d %d\n", m_position[i].chain, m_position[i].distance);
    }
    printf("end of cout_input\n");
    printf("\n");
}



void set_minus_one(int num){
    T[num].left_close = -1;
    T[num].left_close_different =  -1;
}

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

void pre_proces_min_left(){
    set_minus_one(0);
    for(int i = 1; i < size; i++){
        if(m_position[i-1].chain != m_position[i].chain){//zeszły różna siec od aktualnie rozpatrzanego 
            T[i].left_close = i-1;
            if(T[i-1].left_close == -1){
                T[i].left_close_different = -1;
            }
            else if(m_position[T[i-1].left_close].chain != m_position[i].chain){
                T[i].left_close_different = T[i-1].left_close;
            }else{
                T[i].left_close_different = T[i-1].left_close_different;
            }
        }else{//sąsiad jest tą samą siecią więc ma te same najbliższe lewej motele.
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



void reverse_m_postion(){
    for(int i = 0; i < size/2; i ++){
        swap(&m_position[i],&m_position[size-i-1]);
    }
}



void pre_proces_min_right(){
    //reverse_m_postion();
    pre_proces_min_left();
    for(int i = 0; i < size; i ++){
        T[i].right_close = T[size-i-1].left_close;
        T[i].right_close_different = T[size-i-1].left_close_different;
    }
    //reverse_m_postion();
}
void pre_proces_max_right(){
    //reverse_m_postion();
    pre_proces_max_left();
    for(int i = 0; i < 3; i++){
        Right[i] = Left[i];
    }
    //reverse_m_postion();
}
void pre_proces_right(){
    reverse_m_postion();
    pre_proces_max_right();
    pre_proces_min_right();
    reverse_m_postion();
}

void cout_closest(closest_motel A){
    printf("%d %d %d %d\n", A.left_close_different, A.left_close, A.right_close, A.right_close_different);
}



void cout_T(){
    for(int i = 0; i < size; i++){
        cout_closest(T[i]); 
    }printf("\n");
}



int seperation(int A,int B){
    return abs(m_position[A].distance - m_position[B].distance);
}



int find_max_of_closest_values_for_motel(int index){
    if(T[index].left_close == -1 || T[index].right_close == -1){
       //printf("wypad\n");
        return INT_MAX;
    } 
    else if(m_position[T[index].left_close].chain != m_position[size-1-T[index].right_close].chain){
        //printf("close l: %d s: %d r: %d\n", T[index].left_close, index, size-1-T[index].right_close);
        return max(seperation(T[index].left_close, index), seperation(size-1-T[index].right_close, index));
    }else if(T[index].left_close_different == -1 && T[index].right_close_different == -1){
        return INT_MAX;
    }else{
        int Max = -1;
        if(T[index].left_close_different != -1){
            Max = max(Max, max(seperation(T[index].left_close_different, index), seperation(size-1-T[index].right_close, index)));
            //printf("l: %d s: %d r: %d\n", T[index].left_close_different, index, size-1-T[index].right_close);
        }
        if(T[index].right_close_different != -1){
            Max = max(Max, max(seperation(T[index].left_close, index), seperation(size-1-T[index].right_close_different, index)));
            //printf("l: %d s: %d r: %d\n", T[index].left_close, index, size-1-T[index].right_close_different);
        }
        return Max;
    }
}


bool check_if_ok(int L, int index, int R){
    if(L == -1 || R == -1){
        return 0;
    }
    else if(m_position[L].distance > m_position[index].distance || m_position[size-1-R].distance < m_position[index].distance){
        return 0;
    }
    else if(m_position[L].chain != m_position[size-1-R].chain && m_position[index].chain != m_position[size-1-R].chain && m_position[L].chain != m_position[index].chain){
        return 1;
    }
    return 0;
}
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
       // printf("i: %d value : %d\n", i, find_max_of_closest_values_for_motel(i));
        ansmin = min(ansmin, find_max_of_closest_values_for_motel(i));
        ansmax = max(ansmax, find_min_of_furthest_values_for_motel(i));
    }
    if(ansmax == -1 && ansmin == INT_MAX){
        printf("0 0\n");
    }else{
       printf("%d %d",ansmin,ansmax);
    }

}

int main(){
    if(!scanf("%d", &size))printf("WRONG INPUT");
    input();
    //cout_input();
    pre_proces_right();
    //cout_T();
    //pre_proces_max_right();
    //pre_proces_min_right();
    pre_proces_min_left();
    pre_proces_max_left();
    //cout_input();
    //printf("%d: %d: %d: %d: %d :%d\n", Left[0], Left[1], Left[2], Right[0], Right[1], Right[2]);
    //cout_T();
    //pre_proces_min_right();
    answer();
    
}