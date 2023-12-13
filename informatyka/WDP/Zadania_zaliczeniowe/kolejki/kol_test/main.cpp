#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "kol.h"
#include <iostream>
using namespace std;

int main() {
  cout <<"halo"<<endl;
  otwarcie_urzedu(3);
  cout<<" 0:  | 1:  | 2: "<<endl;
  interesant *i0 = nowy_interesant(0);
  cout<<" 0: i0  | 1:  | 2: "<<endl;
  interesant *i1 = nowy_interesant(1);
  cout<<" 0: i0  | 1: i1  | 2: "<<endl;
  interesant *i2 = nowy_interesant(0);
  cout<<" 0: i0, i2  | 1: i1  | 2: "<<endl;
  interesant *i3 = nowy_interesant(0);
  cout<<" 0: i0, i2, i3  | 1: i1  | 2: "<<endl;
  assert(i0 == obsluz(0));
  cout<<" 0: i2, i3  | 1: i1  | 2:"<<endl;
  free(i0);
  interesant *i4 = nowy_interesant(2);
  // 0: i2, i3  | 1: i1  | 2: i4
  interesant *i5 = nowy_interesant(0);
  // 0: i2, i3, i5  | 1: i1  | 2: i4
  show_kolejki();
  zmiana_okienka(i4, 0);
  // 0: i2, i3, i5, i4  | 1: i1  | 2:
  show_kolejki();
  naczelnik(0);
  cout <<"test"<<endl;
  show_kolejki();
  // 0: i4, i5, i3, i2  | 1: i1  | 2:
  std::vector<interesant*> v(fast_track(i5, i2));
  // 0: i4  | 1: i1  | 2:
  cout <<"test2"<<endl;
  assert(v.size() == 3U);
  assert(v[0] == i5);
  assert(v[1] == i3);
  assert(v[2] == i2);
  for (int i = 0; i < 3; ++i)
    free(v[i]);
  assert(!obsluz(2));
  // 0: i4  | 1: i1  | 2:
  naczelnik(0);
  // 0: i4  | 1: i1  | 2:
  interesant *i6 = nowy_interesant(2);
  // 0: i4  | 1: i1  | 2: i6
  interesant *i7 = nowy_interesant(1);
  // 0: i4  | 1: i1, i7  | 2: i6
  assert(i1 == obsluz(1));
  cout <<"test3"<<endl;
  // 0: i4  | 1: i7  | 2: i6
  free(i1);
  show_kolejki();
  zamkniecie_okienka(0, 1);
  // 0:  | 1: i7, i4  | 2: i6
  show_kolejki();
  zamkniecie_okienka(2, 1);
  show_kolejki();
  // 0:  | 1: i7, i4, i6  | 2:
  zamkniecie_okienka(1, 2);
  // 0:  | 1:  | 2: i7, i4, i6
  interesant *i8 = nowy_interesant(0);
  // 0: i8  | 1:  | 2: i7, i4, i6
  show_kolejki(); 
  v = zamkniecie_urzedu();
  // 0:  | 1:  | 2:
  assert(v.size() == 4U);
  assert(v[0] == i8);
  assert(v[1] == i7);
  assert(v[2] == i4);
  assert(v[3] == i6);
  assert(numerek(v[0]) == 8);
  for (int i = 0; i < 4; ++i)
    free(v[i]);
}
