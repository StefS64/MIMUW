#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <climits>
#include <memory>
//#include <iostream>//do wyrzucenia
#include "prev.h"
//using namespace std;
typedef struct node *tree;
struct node {
   tree left;
   tree right;
   int l_val;
   int r_val;
   int previos_in;
};


std::vector <tree> v;

void init(const std::vector<int> &seq){
   for(int i = 0; i < (int)seq.size(); i++){
      pushBack(seq[i]);
   }
}


tree newNode(int left, int right, int val)
{
    tree NEW = (tree)malloc(sizeof(node));
    NEW->left = NULL;
    NEW->right = NULL;
    NEW->r_val = right;
    NEW->l_val = left;
    NEW->previos_in = val;
    return NEW;
}


int findPrevInRange(tree current, int lo, int hi){
   if(current){
      if(lo <= current->l_val && current->r_val <= hi){
         return current->previos_in;
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
   std::shared_ptr<tree> add(new tree);
   std::shared_ptr<tree> temp = add;
   std::shared_ptr<tree> prev = (size) ? v[size-1] : NULL;
   while(l!= r){
      //cout<< l <<" "<< r <<endl;
      s = l/2 + r/2 + ((l%2 && r%2 )? 1 : 0);
      if(val <= s){
         r = s;
         temp->left = newNode(l, r, size);
         if(prev){
            //cout <<"ok"<<endl;
            temp->previos_in = std::max(temp->previos_in,prev->previos_in);
            temp->right=prev->right;
            prev = prev->left;
         }
         //cout <<"ok2"<<endl;
         temp = temp->left;
      }else{
         l = s+1;
         temp->right=newNode(l, r, size);
         if(prev){
            temp->previos_in = std::max(temp->previos_in,prev->previos_in);
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

void destroy(tree a){
   if(a->left){
      destroy(a->left);
   }
   if(a->right){
      destroy(a->right);
   }
   free(a);
}


void done(){
   for(int i = 0 ; i < (int)v.size(); i++){
      destroy(v[i]);
   }
   v.clear();
}