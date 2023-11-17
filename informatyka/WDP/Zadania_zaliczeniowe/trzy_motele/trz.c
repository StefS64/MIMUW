#include <stdio.h>


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



int pre_proces_max[7];//wystarczy mieć po 3 motele z różnych śieci od lewej i od prawej strony tablicy. 

motel m_position[1000000];

closest_motel T[1000000];

int size;

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
}

void set_minus_one(int num){
    T[num].right_close = -1;
    T[num].right_close_different = -1;
    T[num].left_close = -1;
    T[num].left_close_different =  -1;
}
void pre_proces_min_left(){
    set_minus_one(0);
    for(int i = 1; i < size; i++){
        if(m_position[i-1].chain != m_position[i].chain){//zeszły różna siec od aktualnie rozpatrzanego 
            T[i].left_close = i-1;
            if(T[i-1].left_close == -1 || m_position[T[i-1].left_close].chain != m_position[i].chain){
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
    for(int i = 0; i <= size/2; i ++){
        swap(&m_position[i],&m_position[size-i-1]);
    }
}
void pre_proces_min_right(){
    reverse_m_postion();
    pre_proces_min_left();
    for(int i = 0; i < size; i ++){
        T[i].right_close = T[size-i-1].left_close;
        T[i].right_close_different = T[size-i-1].left_close_different;
    }
    reverse_m_postion();
}

void cout_closest(closest_motel A){
    printf("%d %d %d %d\n", A.left_close_different, A.left_close, A.right_close, A.right_close_different);
}
void cout_T(){
    for(int i = 0; i < size; i++){
        cout_closest(T[i]); 
    }
}


int main(){
    if(!scanf("%d", &size))printf("WRONG INPUT");
    input();
    cout_input();
    pre_proces_min_left();
    pre_proces_min_right();
    cout_T();
    
}