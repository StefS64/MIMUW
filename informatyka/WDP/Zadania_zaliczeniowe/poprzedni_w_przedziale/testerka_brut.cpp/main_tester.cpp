#include <cassert>
#include <vector>
#include <iostream>//do wyrzucenia
#include "prev.h"
using namespace std;
int main() {
   int n, q;
   cin >> n >> q;
    std::vector<int> seq;
    int nowy;

    for(int i = 0 ;i < n; i++){
      cin >> nowy;
      seq.push_back(nowy);
    }
    init(seq);
    char co;
    int a, lo ,hi;
    for(int i = 0; i < q ;i ++){
      cin >> co;
      if(co == 'a'){
         cin >> nowy;
         pushBack(nowy);
      }else if (co == 'q'){
         cin >> a >> lo >> hi;
         cout<<prevInRange(a,lo,hi)<<'\n';
      }
   }
   done();
}