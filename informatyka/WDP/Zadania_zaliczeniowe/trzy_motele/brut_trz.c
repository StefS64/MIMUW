#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
int min(int a, int b){
    return a > b ? b : a;
}
int max(int a, int b){
    return a > b ? a : b;
}
bool parami_rozne(int a,int b,int c){
    if(a != b && b != c && c != a){
        return true;
    }
    return false;
}
int main(){
    int n;
    assert(scanf("%d",&n) == 1);
    int *num_motel = (int*)malloc((long unsigned int)n  * sizeof(int));
    int *miejsce_motel = (int*)malloc((long unsigned int)n * sizeof(int));
    for(int i = 0 ; i < n; i++){
        if(!scanf("%d%d", &num_motel[i], &miejsce_motel[i]))printf("wrong input");
    }
   /* for(int i = 0 ; i <n; i++){
        printf("%d %d\n", num_motel[i], miejsce_motel[i]);
    }*/
    int minim = INT_MAX , maxi = -1;
    for(int a = 0; a < n; a++){
        for(int b = a+1; b < n; b++){
            for(int c = b+1; c < n; c++){
                if(parami_rozne(num_motel[a], num_motel[b], num_motel[c])){
                    //printf("%d %d %d\n", a, b, c);
                    maxi = max(maxi, min(miejsce_motel[b] - miejsce_motel[a], miejsce_motel[c] - miejsce_motel[b]));
                    minim = min(minim,max(miejsce_motel[b] - miejsce_motel[a], miejsce_motel[c] - miejsce_motel[b]));
                }
            }
        }

    }
    if(maxi == -1 && minim == INT_MAX){
        printf("0 0\n");
    }else{
        printf("%d %d\n", minim, maxi);
    }
}