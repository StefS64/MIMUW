#include <stdio.h>
#include <cstdlib>
using namespace std;
typedef struct node *bin_tree;
struct node{
   int val;
   bin_tree left, right;
}node;
void destroy(bin_tree a){
   if(a->left){
      destroy(a->left);
   }
   if(a->right){
      destroy(a->right);
   }
   free(a);
}
void show_tree(bin_tree a){
   if(a){
      printf("%d", a->val);
      show_tree(a->left);
      show_tree(a->right);
   }
}
bin_tree bestify(bin_tree t, bin_tree ok){
   if(t->left){
      if(t->left->val > t->val){
         destroy(t->left);
         ok->left = NULL;
      }else{
         ok->left = bestify(t->left, ok->left);
      }
   }
   if(t->right){
      if(t->right->val < t->val){
         destroy(t->right);
         ok->right = NULL;
      }else{
         ok->right = bestify(t->right, ok->right);
      }
   }
   return ok;

}
bin_tree newNode(int data)
{
    // Allocate memory for new node
    bin_tree node = (bin_tree)malloc(sizeof(node));
 
    // Assign data to this node
    node->val = data;
 
    // Initialize left and
    // right children as NULL
    node->left = NULL;
    node->right = NULL;
    return (node);
}
int main(){
   bin_tree tree = newNode(1);
   tree->left = newNode(2);
   tree->left->right = newNode(4);
   tree->right = newNode(3);
   //show_tree(tree);
   tree = bestify(tree,0);
   show_tree(tree);
}