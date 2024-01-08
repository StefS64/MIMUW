#include <iostream>
#include <vector>
using namespace std;

int dy[8] = {1,2,2,1,-1,-2,-2,-1};
int dx[8] = {2,1,-1,-2,-2,-1,1,2};


bool czy_ok(int x, int y,int n,int m, vector<vector<int>> &odw){
   if(odw[x][y]|| x < 0 || y < 0 || y >= m || x >= n){
      return 0;
   }
   return 1;
}
bool przechodzenie(int x, int y, vector <int> &v, int Size, vector<vector<int>> &odw){
   cout <<"guten tag"<<endl;
   odw[x][y] = 1;
   if((int)v.size() == Size){
      return 1;
   }
   for(int i = 0; i < 8; i++){
      if(czy_ok(x+dx[i], y+dy[i], odw.size(), odw[0].size(), odw)){
         v.push_back(i);
         x+=dx[i];
         y+=dy[i];
         if(przechodzenie(x, y, v, Size, odw)){
            return 1;
         }
         x-=dx[i];
         y-=dy[i];
         v.pop_back();
      }
   }
   odw[x][y] = 0;
   return 0;
}


int main(){
   int n,m;
   cin >> n>>m;
   //vector<vector<int>> odw;
  /* for(int i = 0; i < n; i ++){
      vector<int> New;
      for(int j = 0; j < m; j++){
         New.push_back(0);
      }
      odw.push_back(New);
   }*/
   cout <<"START"<<endl;
   vector<vector<int>> odw(n, vector<int> (m, 0));
   vector<int>wyn;
   if(przechodzenie(0, 0, wyn, n*m, odw)){
      int x = 0,y = 0;
      cout <<"0 0"<<endl;
      for(auto i : wyn){
         cout <<x + dx[i]<<" "<<y +dy[i]<<endl;
      }
   }

}