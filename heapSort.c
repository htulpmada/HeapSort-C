#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "node.h"

//heapsort using complete binary tree not array for implementation
//made by Adam Pluth
//cs 201 
//2/12/16


/* options */
int explain= 0;    /* option -v  */
int reverse = 0;     /* option -d  */

int ProcessOptions(int,char **);
void Fatal(char *,...);
void readInFile(char arg[],int m);
void levelOrderTraversal(node* root,int len,int Switch,int m);
void Insert(node **root,int data,List* l);


int main(int argc,char **argv){
	int i=0;
	int m;
	int argIndex;
	if (argc == 1) Fatal("%d arguments!\n",argc-1);
	argIndex = ProcessOptions(argc,argv);
	m=reverse;
	if (argIndex == argc)printf("No arguments\n");
	else{
		i=argIndex;
		readInFile(argv[i],m);
	}
	return 0;
}
void Fatal(char *fmt, ...){
    va_list ap;
    fprintf(stderr,"An error occured: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    exit(-1);
    }
void Explain(){
	printf("\nAdam Pluth's explaination for n log n time:\n\n as we read in the integers from the file we are using n time, we create a node for each integer used and add this to a queue, we do this as we read them in as to not use anymore time than needed.  After the numbers have been read, we take the queue and dequeue it and starting a new list, this is the begining of our level traversal, we put these nodes on to a stack used for reverse level order traversal.  on previously mentioned reverse traversal we will dequeue off of a stack and heapify each node as we move along. heapifying a node consists of bubbleing up each node while also bubbling down each parent node we swap with. after all that we end with extracting that min value, max if argument given. By extracting the min/max we will swap root with last node added, using reverse traversal to keep track of position,and bubble down the new root to reconfirm heap srtucture of the tree.");
	exit(0);
}
int ProcessOptions(int argc, char **argv){
    int argIndex;
    argIndex = 1;
    while (argIndex < argc && *argv[argIndex] == '-')
        {   
        switch (argv[argIndex][1])
            {
			case 'v':
                Explain();
		break;
            case 'd':
                reverse= 1;
                break;
            default:
                Fatal("option %s not understood\n",argv[argIndex]);
            }
		++argIndex;
        }
	return argIndex;
}
void readInFile(char arg[],int m){
	FILE *ifp;
	int i=0;
	char integ[20];
	int integer=0;
	int dig=0;
	struct node* root=NULL;
	struct List* list=newLNode(100000000);//estimated size of data input
	ifp = fopen(arg, "r");
	if (ifp == NULL){
		fprintf(stderr, "Can't open input file in.list!\n");
		exit(1);
	}
	while (fscanf(ifp, "%20s", integ)!=EOF){//reading one digit at a time
		i++;
		if(integ[dig]==' '||integ[dig]=='\n'){
		dig=0;
		continue;
		} //end of number
		dig++;
		integer=atoi(integ);
		Insert(&root,integer,list);
	}
	fclose(ifp);	
	levelOrderTraversal(root,i,3,m);//3=heapify option
	levelOrderTraversal(root,i,4,m);//4=print min/max option 
}



void levelOrderTraversal(node* root,int len,int Switch,int m){
	List* list1=newLNode(len);
	List* list2=newLNode(len);
	//printf("level order\n");
	Enq(root,list1);
	while(!isEmpty(list1)){
		node* temp = Deq(list1);
		//do somthing here//
		Enq(temp,list2);//make reverse level with stack
		if(Switch==2){//level order traversal
			printf("%i\n",temp->data);
		}
		if(temp->Left){Enq(temp->Left,list1);}
		if(temp->Right){Enq(temp->Right,list1);}
	}
	if(Switch==3){	//reverse level order for heapifying
		while(!isEmpty(list2)){
			node* temp2 = Pop(list2);
			BubbleUp(temp2,root,m);
			}
	}
	if(Switch==4){	//remove min/max
		//if(m==0){printf("min followed by");}
		//if(m==1){printf("max followed by");}
		while(!isEmpty(list2)){
			node* temp2 = Pop(list2);
			Extract(temp2,root,m);
			printf("%i ",temp2->data);
			}
	}
}

void Insert(node **root,int data,List* l){
	node *temp = newHNode(data);
	if(*root==NULL){
		*root=temp;
	}
	else{
	node* front=getFront(l);
	if(front->Left==NULL){front->Left=temp;temp->Parent=front;}
	else if(front->Right==NULL){front->Right=temp;temp->Parent=front;}
	if(hasBothChildren(front)){Deq(l);}
	}
	Enq(temp,l);
}
