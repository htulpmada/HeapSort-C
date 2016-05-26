#include <stdio.h>
#include <stdlib.h>
//#include "node.c"
#include "list.h"

List * newLNode(int v){
        List *p=(List*) malloc(sizeof(List));
        p->len = v;
	p->front=p->rear=-1;
	p->array=(node**) malloc(p->len * sizeof(node*));
	p->i=0;
//	for(p->i;p->i<v;++p->i){p->array[p->i]=NULL;}
	p->i=0;
	return p;
        }


node* getFront(List* l){return l->array[l->front];}
node* getRear(List* l){return l->array[l->rear];}

int hasOnlyOne(List* l){return l->front==l->rear;}
int isEmpty(List* l){return l->front==-1;}
int isFull(List* l){return l->rear==l->len;}

void Enq(node *root, List* l){
	if(isFull(l)){printf("full\n");return;}
	l->array[++l->rear]=root;
	if(isEmpty(l)){++l->front;}
}

node* Deq(List* l){
	if(isEmpty(l)){printf("Empty\n");return NULL;}
	l->temp = getFront(l);
	if(hasOnlyOne(l)){l->front=l->rear=-1;}
	else{ ++l->front;}
	return l->temp;
}

node* Pop(List* l){
	if(isEmpty(l)){printf("Empty\n");return NULL;}
	l->temp = getRear(l);
	if(hasOnlyOne(l)){l->front=l->rear=-1;}
	else{ --l->rear;}
	return l->temp;
}

