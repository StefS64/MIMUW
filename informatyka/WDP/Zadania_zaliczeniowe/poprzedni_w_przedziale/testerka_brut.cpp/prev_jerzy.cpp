#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//Zakres elementów z ciągu, MIN domknięty, MAX otwarty
long long const MIN = INT_MIN;
long long const MAX = (long long)INT_MAX + 1;

//Wierzchołki drzewa binarnego
typedef struct node{
    node *left, *right; //Wskażniki na prawe i lewe dziecko
    long long range_min, range_max; //Zakres numerów tego wierzchołka, min domknięty, max otwarty
    int val; //Ostatni w tym zakresie
} node;

std::vector<node*> memory; //Wskaźniki na poprzednie stany drzewa

node* addNode(long long range_min, long long range_max, int val){
    node* nodeptr = (node*) malloc (sizeof(node));
    nodeptr->left = nullptr;
    nodeptr->right = nullptr;
    nodeptr->range_min = range_min;
    nodeptr->range_max = range_max;
    nodeptr->val = val;
    return nodeptr;
}

void pushBack(int value){
    int static numbers = 0;
    memory.push_back(addNode(MIN, MAX, numbers));
    
    long long range_min = MIN;
    long long range_max = MAX;
    long long mid = 0;

    node *new_node = memory[numbers];
    node *old_node; //Kopia obsługiwanego wierzchołka z poprzedniej wersji drzewa (być może nullptr)
    if(numbers > 0){old_node = memory[numbers-1];}
    else{old_node = nullptr;}
    
    while(range_min < range_max - 1){
        mid = (range_min + range_max)/2;
        if(value < (int) mid){
            range_max = mid;
            new_node->left = addNode(range_min, range_max, numbers);
            if(old_node){
                new_node->right = old_node->right;
                old_node = old_node->left;
            }
            new_node = new_node->left;
        }else{
            range_min = mid;
            new_node->right = addNode(range_min, range_max, numbers);
            if(old_node){
                new_node->left = old_node->left;
                old_node = old_node->right;
            }
            new_node = new_node->right;
        }
    }
    numbers++;    
}


void init(const std::vector<int> &seq){
    for(auto num: seq){
        pushBack(num);
    }
}

//Funkcja pomocnicza wyszukująca rekurencyjnie poprzedni w zakresie
//searchRangeMin i searchRangeMax opisują szukany zakres, rangeMin i rangeMax to zakres obsługiwanego wierzchołka
int prevInRangeRecursion(node *n, long long searchRangeMin, long long searchRangeMax, long long rangeMin, long long rangeMax){
    //Jeśli to pojedynczy element ciągu
    if(rangeMin + 1 == rangeMax){return n->val;} 
    
    //Jeśli cały szukany przedział zwiera się w tym zakresie
    if(searchRangeMin <= rangeMin && rangeMax <= searchRangeMax){return n->val;} 
    
    long long mid = (rangeMin + rangeMax)/2;
    if(searchRangeMax <= mid){
        if(!n->left){return -1;}
        else{return prevInRangeRecursion(n->left, searchRangeMin, searchRangeMax, rangeMin, mid);}
    }else if(searchRangeMin >= mid){
        if(!n->right){return -1;}
        else{return prevInRangeRecursion(n->right, searchRangeMin, searchRangeMax, mid, rangeMax);}
    }else{
        int max = -1;
        if(n->left){max = prevInRangeRecursion(n->left, searchRangeMin, searchRangeMax, rangeMin, mid);}
        if(n->right){max = std::max(max, prevInRangeRecursion(n->right, searchRangeMin, searchRangeMax, mid, rangeMax));}
        return max;
    }
}

int prevInRange(int i, int lo, int hi){
    return prevInRangeRecursion(memory[i], lo, hi + 1, MIN, MAX);
}

void done(){
    //Usuwa od końca kolejne wersje drzewa
    for(long long i = (long long)memory.size() - 1; i >= 0; i--){
        node *nod = memory[i], *temp;
        memory.pop_back();
        while(nod->range_min != nod->range_max - 1){
            if(nod->right && nod->right->val == nod->val){
                temp = nod->right;
                free(nod);
                nod = temp;
            }else if(nod->left && nod->left->val == nod->val){
                temp = nod->left;
                free(nod);
                nod = temp;
            }
        }
        free(nod);
    }
    return;
}