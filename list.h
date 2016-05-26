#include "node.c"
typedef struct List
{
	int front,rear;
	int len;
	int i;
	struct node* temp;
	struct node* *array;
}List;

List * newLNode(int len);
int isEmpty(List* l);
int isFull(List* l);
int hasOnlyOne(List* l);
node* getFront(List* l);
node* getRear(List* l);
node* Deq(List* l);
node* Pop(List* l);
void Enq(node *root, List* l);

