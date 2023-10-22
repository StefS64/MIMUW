#include <bits/stdc++.h>
using namespace std;
vector<int>T[100007];
const int MAX_INT = 1e9+7;
pair<int,int> MAX_PAIR = {MAX_INT,MAX_INT};
int weight[100007];
int num[100007];
int n;
int liczba = 1;
pair <int ,int> zap[100007];
void DFS(int x,int father){
    int siz = T[x].size();
    zap[x].first = liczba;//poczatek przedziału
        for(int i = 0; i < siz;i++){
            if(T[x][i]!= father){
                DFS(T[x][i],x);
            }
        }
        zap[x].second = liczba;
        num[liczba] = x;//prawdziwy numer
        liczba++;
        //sub_tree[x] = min(sub_tree[x],weight[x]);
}

pair<int,int> tree[200008];
int WHOLE_TREE = 1,base;
void cout_tree(){
    int pot = 1;
    for(int i = 1;i < WHOLE_TREE;i++){
        cout<<tree[i].first<<" ";
        if(i == pot){
            cout <<endl;
            pot*=2;
            pot++;
        }
    }
}

void intit_tree(int x){
    while(WHOLE_TREE < x){
        WHOLE_TREE*=2;
    }
    base = WHOLE_TREE;
    WHOLE_TREE*=2;
    for(int i = 1; i <= n;i++){
        tree[base+i-1].first = zap[num[i]].second; 
        tree[base+i-1].second = i;
    }
    for(int i = n+1; i <= WHOLE_TREE;i++){
        tree[base+i-1].first = MAX_INT;
        tree[base+i-1].second = i;
    }
    int Y = base-1;
    cout << Y <<endl;
    while(Y > 0){
        tree[Y] = min(tree[2*Y],tree[2*Y+1]);
        Y--;
    }
}
pair<int ,int> query(int x,int y){
    
    int l = base + x-1, r = base+y-1;
    
    pair<int,int> minim = {MAX_INT,MAX_INT};
    if(l<r)minim = min(tree[l],tree[r]);
    while(l < r){
        if(l%2 == 1){
            l++;
            minim = min(minim, tree[l]);
        }
        if(r%2 == 0){
            r--;
            minim = min(minim, tree[r]);
        }
         l/=2;
         r/=2;
    }
    return minim;
}
void update(int x){
    x+=base-1;
    tree[x].first = MAX_INT;
    x/=2;
    while(x > 0){
        tree[x] = min(tree[2*x],tree[2*x+1]);
        x/=2;
    }
}
int main(){         

    cin >> n;
    int num;
   
    for(int i = 1; i <n; i ++){
        cin >> num;
        T[num].push_back(i+1);
        T[i+1].push_back(num);
    }
     for(int i = 1; i <=n; i ++){
        cin >> weight[i];
    }
    DFS(1,-1);
    intit_tree(n);
    cout_tree();

     for(int i = 1; i <= n; i ++){
        int siz = T[i].size();
        for(int j = 0; j < siz;j++){
            cout<< T[i][j]<<" ";
        }cout <<endl;
    }
    for(int i = 1; i <=n; i ++){
        cout << zap[i].first<<" "<<zap[i].second<<'\n';
    }cout <<endl;
    /*int q,a,b;
    cin >> q;
    for(int i = 0 ; i < q; i++){
        cin >> a >> b;
        cout<<query(a,b).first<<endl;
        update(query(a,b).second);
        cout_tree();
    }*/
    int jump[n+1];
    int x = 1;
    while(n > 0){
        if(query(zap[x].first, zap[x].second-1) != MAX_PAIR){
            
        }else{
            cout <<x<<" ";
        }
    }

}