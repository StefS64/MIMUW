#include <stdio.h>
int T[10000000+7];
int max(int a, int b){
    return (a>b ? a : b);
}
int main(){
    int n, Max = 0;
    //int *t = (int*) malloc(n*sizof(int))
    if(scanf("%d",&n) == 1);
    for(int i = 0; i < n; i++){
        scanf("%d", &T[i]);
    }
    int right = n-1;
    int ans = 1;
        for(int i = n-2; i >= 0 ;i--){
                if(T[i] == 0){
                    i--;
                    Max = max(Max,ans);
                    ans = 1;
                    while(i >=0){
                        if(T[i] == 0){
                            Max =max(Max,ans);
                            ans = 1;
                        }else{
                            ans++;
                        }
                        i--;
                    }
                }else if(T[right]%T[i] != 0){
                        Max = max(ans,Max);
                        right = i;
                        ans = 1;
                }
                else{
                        ans++;
                }
                Max = max(Max,ans);
        }
    printf("%d\n",Max);
}
