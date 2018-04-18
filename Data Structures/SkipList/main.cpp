#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Node {
    int val;
    int height;
    struct Node** next;
} Node;

typedef struct SkipList {
    int max_height;
    Node* start;
    Node* end;
} SkipList;

int getHeight(int max_h) {
    int h = 1;
    float p = 0.8;
    while (h < max_h && rand() / (RAND_MAX + 1.) < p) h++;
    return h;
}


Node* newNode(int val, int max_height) {
    Node* n = malloc(sizeof(Node));
    n->val = val;
    n->height = getHeight(max_height);
    n->next = malloc(sizeof(Node*)*n -> height);
    for(int i = 0; i < n -> height; i++)
        n -> next[i] = NULL;
    return n;
}

void deleteNode(Node* n) {
    free(n->next);
    free(n);
    // remove Node from memory
}

SkipList* newSkipList(int max_height) {
    SkipList* list = malloc(sizeof(SkipList));
    list->max_height = max_height;

    // allocate list->start and list->end
    // initialize height and next for each one

    list->start=malloc(sizeof(Node));
    list->start->height=max_height;
    list->start->next=malloc(sizeof(Node*)*list->start->height);

    list->end=malloc(sizeof(Node));
    list->end->height=max_height;
    list->end->next=malloc(sizeof(Node*)*list->end->height);

    for(int i=0; i<max_height; i++) {
        list->start->next[i] = list->end;
        list->end->next[i] = NULL;
    }

    return list;
}

void deleteSkipList(SkipList* list) {
    Node *first = list -> start;
    while(first != NULL){
        Node *tmp = first;
        first = first -> next[0];
        deleteNode(tmp);
    }
    free(list);
    // call deleteNode() on every node in skiplist
    // call free() on list
}

void insert(SkipList* list, Node* node) {
    Node* tmp = list->start;
    int i = list->max_height - 1;
    Node *newArr[list -> max_height];
    while (i >= 0) {
        // while value of tmp->next[i] is less than value of given node, go ahead
        while(tmp->next[i]!=list->end && tmp->next[i]->val < node->val)
            tmp = tmp->next[i];

        newArr[i] = tmp;
        // if i isn't too high - insert (plug) given node on level 'i'
        i--;
    }
    for(int j = 0; j < node -> height; j++){
        node -> next[j] = newArr[j] -> next[j];
        newArr[j] -> next[j] = node;
    }
}

Node* find(SkipList* list, int val) {
    Node* tmp = list->start;
    int i = list->max_height - 1;
    while (i >= 0) {
        // while value of tmp->next[i] is less than value of given node, go ahead
        while (tmp->next[i] != list->end && tmp->next[i]->val < val) {
            tmp = tmp -> next[i];
        }
        i--;
    }
    // return desired node or NULL if such value doesn't exist in the skiplist
    if(tmp -> next[0] != list -> end  && tmp -> next[0] -> val == val) return tmp -> next[0];
    return NULL;
}

void removeFromList(SkipList* list, Node* node) {
    if(node == NULL) return;
    Node* tmp = list->start;
    int i = node->height - 1;
    while (i >= 0) {
        // while value of tmp->next[i] is less than value of given node, go ahead
        while(tmp -> next[i] != node)
            tmp = tmp -> next[i];

        tmp -> next[i] = node -> next[i];
        // remove (unplug) given node on level 'i'
        i--;
    }
}

int main(int argc, char** argv) {
    /*
     * test data:
     * Z - number of test cases
     * h, I, R, F - max height of single node (h), number of values to insert (I), remove(R) and find (F)
     * I values to insert
     * R values to remove (should exist in the previous set)
     * F values to find
     * Output:
     * F lines, "y" or "n" in each one - depending on whether given value is present in the skiplist or not
    */
    srand(time(NULL));
    int Z;
    scanf("%d", &Z);

    for (int i=0; i<Z; i++) {
        int h, I, R, F;
        scanf("%d", &h);
        scanf("%d", &I);
        scanf("%d", &R);
        scanf("%d", &F);

        SkipList* list = newSkipList(h);
        int x;
        // insert
        for(int j=0; j<I; j++) {
            scanf("%d", &x);
            insert(list, newNode(x, h));
        }
        // remove
        for(int j=0; j<R; j++) {
            scanf("%d", &x);
            Node* n = find(list, x);
            removeFromList(list, n);
            deleteNode(n);
        }
        // find
        for(int j=0; j<F; j++) {
            scanf("%d", &x);
            printf("%s\n", find(list, x) == NULL ? "n" : "y");
        }
        // cleanup
        deleteSkipList(list);
    }
}
