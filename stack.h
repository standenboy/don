typedef struct stack {
	int *sp;
	int value;
	int *stack;
} stack;

stack *initstack(int value, size_t size);
