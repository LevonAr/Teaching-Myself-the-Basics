#include <stdlib.h>
#include <stdio.h>


append( struct node **q, int num);
struct node{
    int data;
    struct node *link;
};

int main(){
    struct node *p; //pointer to node structure
    p = NULL;   //linked list is empty

    append( &p,1);
    return 0;
}

append( struct node **q, int num){
    struct node *temp, *r;  //two pointers to struct node
    temp = *q;

    if(*q == NULL){
        temp = malloc(sizeof(struct node));
        temp -> data = num;
        temp -> link = NULL;
        *q = temp;
    }
    else{
        temp = *q;
        while( temp -> link != NULL)
            temp = temp -> link;
        r = malloc(sizeof(struct node));
        r -> data = num;
        r -> link = NULL;
        temp -> link = r;
    }
}
