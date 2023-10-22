#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin >> t;
    while(t--){
        int n,odd = 0,sum = 0,num;
        cin >> n;
        for (int i = 0 ; i < n; i++ ){
            cin >> num;
            if(num % 2 == 1){
                odd++;
                sum+=(num-1);
            }else{
                sum+=num;
            }
        }
        if(odd != 0){
            cout <<1+sum/(2*odd)*2<<'\n';
        }else{
            cout << sum<<'\n';
        }
    }

}