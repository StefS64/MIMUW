#include <vector>
#include <cstdlib>
#include <climits>
#include <memory>
#include "prev.h"
using namespace std;

class node {
   private:
   typedef shared_ptr <node> tree;
   public:
   tree left;
   tree right;
   int l_val;//lewa granica przedzialu
   int r_val;//prawa granica przedzialu
   int previous_in;//indeks prev_in_range dla aktualnego drzewa 
};


typedef shared_ptr <node> tree;


vector <tree> v;//vector przechowujący wskaźniki na poprzednie stany drzewa


void init(const std::vector<int> &seq){
   for(int i = 0; i < (int)seq.size(); i++){
      pushBack(seq[i]);
   }
}


tree newNode(int left, int right, int previous){
   node new_node = {nullptr, nullptr, left, right, previous};
   return make_shared <node>(new_node);
}

/*
Funkcja sprawdza czy te odcinki mają niepuste przecięcię zakłada prawdziwość: a <= b i c <= d 
*/

bool non_empty_intersection(int a, int b, int c ,int d){
   if(a > d || b < c){
      return 0;
   }else{
      return 1;
   }
}
/*
Funkcja findPrevInRange zwraca największy indeks z drzewa current, 
który znajduje się w przedziale od lo do hi.
*/

int findPrevInRange(tree current, int lo, int hi){
   if(current && non_empty_intersection(lo, hi, current->l_val, current->r_val)){
      if(lo <= current->l_val && current->r_val <= hi){
         return current->previous_in;
      }
      return max(findPrevInRange(current->left, lo, hi), findPrevInRange(current->right, lo, hi));
   }else{
      return -1;
   }
}


int prevInRange(int i, int lo, int hi){
   return findPrevInRange(v[i], lo, hi);
}

/*
Funkcja create_tree(int val) tworzy nowe drzewo.
Już istniejące wierzchołki dopina do odpowiednich wskaźników tworzonego drzea
*/

tree create_tree(int val){
   int size = (int)v.size();
   int l = INT_MIN, r = INT_MAX, s = 0;
   tree add = newNode(l, r, size);
   tree temp = add;
   tree prev = (size) ? v[size-1] : nullptr;
   while(l != r){
      s = (int)(((unsigned long long)r + (unsigned long long)l)/2);
      if(val <= s){
         r = s;
         temp->left = newNode(l, r, size);
         if(prev){
            temp->right = prev->right;
            prev = prev->left;
         }
         temp = temp->left;
      }else{
         l = s+1;
         temp->right = newNode(l, r, size);
         if(prev){
            temp->left = prev->left;
            prev = prev->right;
         }
         temp = temp->right;
      }
   }
   return add;
}


void pushBack(int value){
   tree New = create_tree(value);
   v.push_back(New);
}


void done(){
   v.clear();
}
