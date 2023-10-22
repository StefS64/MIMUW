#include <bits/stdc++.h>
using namespace std;
int main (){
    ios_base::sync_with_stdio(0);
      cin.tie(0);
      cout.tie(0);
   string s;
   long long size,one_min = -1,one_max = -1,num_of_1=0;
   cin >> s;

   size = s.size();
    for(int i = 0 ; i < size; i++){
        if(s[i] == '1'){
            num_of_1++;
            one_max = i;
            if(one_min == -1){
                one_min = i;
            }
        }
    }
    if(one_max == -1 && one_min == -1){
        cout << "0" <<'\n';
        return 0;
    }
   //cout << one_max<<" "<< one_min<<'\n';
    long long l_zero_max=-1,l= 0,r_zero_max = -1,dlu = 0,Max = 0;
    for(int i = one_min+1; i <= one_max;i++){
        if(s[i] == '0'){
            dlu++;
            if(s[i-1] == '1'){
                l = i;
            }
        }else{
            if(s[i-1] == '0'){
                if(Max < dlu){
                    Max = dlu;
                    r_zero_max = i-1;
                    l_zero_max = l;
                    dlu = 0;
                }
            }
        }
    }
    if(r_zero_max == -1){
        cout<< num_of_1*4+7*min(one_max,size-one_min);
        return 0;
    }
    //cout << l_zero_max<<" "<<r_zero_max<<'\n';
        cout << num_of_1*4+7*min(min(one_max,size-one_min),size - r_zero_max-1 + l_zero_max-1+min(size - r_zero_max-1,l_zero_max-1));
        return 0;

    
}