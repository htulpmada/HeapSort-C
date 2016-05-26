#include <stdio.h>
#include <stdlib.h>
#include "node.h"

node * newHNode(int value)
        {
        node *p = (node*) malloc(sizeof(node));
        p->data = value;
	p->Left=NULL;
	p->Right=NULL;
	return p;
        }

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


int hasBothChildren(node* temp){
	return temp && temp->Left &&temp->Right;
}
void Extract(node* temp,node* root,int m){
	node *t = newHNode(temp->data);
	if(temp==root){return;}
	else{
		if(temp->Parent->Left==temp){
			//printf("xtracting left child\n");
			temp->Parent->Left=NULL;
		}
		if(temp->Parent->Right==temp){
			//printf("xtracting right child\n");
			temp->Parent->Right=NULL;
		}
		temp->data=root->data;
		root->data=t->data;
		BubbleDown(root,m);
	}
}

void BubbleUp(node* temp,node* r,int m){//m=(min=0),(max=1) 
	int i=0;
	if(m==0){//min ordered
		while(temp!=r){
			if(temp->Parent==NULL){break;}
			if(temp->data<temp->Parent->data){
				i=temp->data;
				temp->data=temp->Parent->data;
				temp->Parent->data=i;
				BubbleDown(temp,m);
				temp=temp->Parent;
				continue;
			}
			else{
				//not bubling
				break;
			}
		}
	}
	else{//max ordered
		while(temp!=r){
			if(temp->Parent==NULL){break;}
			if(temp->data>temp->Parent->data){
				i=temp->data;
				temp->data=temp->Parent->data;
				temp->Parent->data=i;
				BubbleDown(temp,m);
				temp=temp->Parent;
				continue;
			}
			else{
				//not bublin
				break;
			}
		}
	}
}
void BubbleDown(node* temp,int m){
	int i=0;
	if(m==0){//min ordered
		while(temp!=NULL){
			if(temp==NULL){break;}
			if(temp->Left!=NULL&&temp->data>temp->Left->data){
				if(temp->Left==NULL){break;}//at leaf node
				if(temp->Right==NULL){break;}//at leaf  node
				if(temp->Right->data<temp->Left->data){//check for smallest child value					
					//right child smaller					
					i=temp->data;
					temp->data=temp->Right->data;
					temp->Right->data=i;
					temp=temp->Right;
					continue;
				}
				//left child smaller
				i=temp->data;
				temp->data=temp->Left->data;
				temp->Left->data=i;
				temp=temp->Left;
				continue;
			}
			else if(temp->Right!=NULL&&temp->data>temp->Right->data){//checks right child if doesnt have left child
				// should never do this do to level order construction
				if(temp->Right==NULL){break;}
				i=temp->data;//swap right child
				temp->data=temp->Right->data;
				temp->Right->data=i;
				temp=temp->Right;
				continue;
			}
			else{
				//not bublin
				break;
			}
		}
	}
	else{
		//max ordered same code as above but for max ordered
		while(temp!=NULL){
			if(temp==NULL){break;}
			if(temp->Left!=NULL&&temp->data<temp->Left->data){
				if(temp->Left==NULL){break;}
				if(temp->Right==NULL){break;}
				if(temp->Right->data>temp->Left->data){
					//swap to right
					i=temp->data;
					temp->data=temp->Right->data;
					temp->Right->data=i;
					temp=temp->Right;
					continue;
				}
				//swap to Left
				i=temp->data;
				temp->data=temp->Left->data;
				temp->Left->data=i;
				temp=temp->Left;
				continue;
			}
			else if(temp->Right!=NULL&&temp->data<temp->Right->data){
				if(temp->Right==NULL){break;}
				i=temp->data;//swap to right
				temp->data=temp->Right->data;
				temp->Right->data=i;
				temp=temp->Right;
				continue;
			}
			else{
				//not bubling
				break;
			}
		}
	}
}

