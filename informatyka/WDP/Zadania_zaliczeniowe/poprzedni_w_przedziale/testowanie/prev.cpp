#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <climits>
#include <memory>
#include <iostream>//do wyrzucenia
#include "prev.h"
using namespace std;
class node {
   private:
   typedef shared_ptr <node> tree;
   public:
   tree left;
   tree right;
   int l_val;
   int r_val;
   int previous_in;
};
typedef shared_ptr <node> tree;
std::vector <tree> v;

void init(const std::vector<int> &seq){
   for(int i = 0; i < (int)seq.size(); i++){
      pushBack(seq[i]);
   }
}


tree newNode(int left, int right, int val)
{
   node new_node = {nullptr, nullptr, left, right, val};
   return make_shared <node>(new_node);
}


int findPrevInRange(tree current, int lo, int hi){
   if(current){
      if(lo <= current->l_val && current->r_val <= hi){
         return current->previous_in;
      }
      return std::max(findPrevInRange(current->left, lo, hi), findPrevInRange(current->right, lo, hi));
   }else{
      return -1;
   }
}

int prevInRange(int i, int lo, int hi){
  return findPrevInRange(v[i], lo, hi);
} // max{ j : 0 <= j <= i && seq[j] \in [lo..hi] } or -1

tree create_tree(int val){
    //cout <<"siema val:"<<val<<endl;
   int size = (int)v.size();
   int l = INT_MIN, r = INT_MAX, s = 0;
   tree add = newNode(l, r, size);
   tree temp = add;
   tree prev = (size) ? v[size-1] : nullptr;
   while(l!= r){
      //cout<< l <<" "<< r <<endl;
      s = l/2 + r/2 + ((l%2 && r%2) ? 1 : 0);
      if(val <= s){
         r = s;
         temp->left = newNode(l, r, size);
         if(prev){
            //cout <<"ok"<<endl;
            temp->previous_in = std::max(temp->previous_in,prev->previous_in);
            temp->right=prev->right;
            prev = prev->left;
         }
         //cout <<"ok2"<<endl;
         temp = temp->left;
      }else{
         l = s+1;
         temp->right=newNode(l, r, size);
         if(prev){
            temp->previous_in = std::max(temp->previous_in,prev->previous_in);
            temp->left=prev->left;
            prev = prev->right;
         }
         temp = temp->right;
      }
   }
   return add;
}

void pushBack(int value){
   tree NEW = create_tree(value);
   //cout<<"zabawa"<<endl;
   v.push_back(NEW);
}

void done(){
   v.clear();
}