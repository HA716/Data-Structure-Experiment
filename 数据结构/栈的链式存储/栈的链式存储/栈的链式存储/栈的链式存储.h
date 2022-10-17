typedef struct STACKNODE
{
	struct STACKNODE *next;
}StackNode;

typedef struct STACK_LINKLIST
{
	StackNode header;  //Õ»¶¥½áµã
	int size;
}LStack;
void * Init();
void Push(void*myStack, void *data);
void Pop(LStack * stack);
StackNode * TopElement(LStack*stack);
void Free(LStack*stack);







