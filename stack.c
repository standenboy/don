#include <stddef.h>
#include <stdlib.h>

typedef struct stack {
	int *sp;
	int value;
	int *stack;
} stack;

int pop(stack *stack){
	stack->sp -= sizeof(int);
	int i = *stack->sp;
	*stack->sp = stack->value;
	return i;
}

void push(stack *stack, int value){
	*stack->sp = value;
	stack->sp += sizeof(int);
}

void deinitstack(stack *stack){
	free(stack->stack);
	free(stack);
	stack = NULL;
}

stack *initstack(int value, size_t size){
	stack *s = malloc(sizeof(stack));
	s->stack = calloc(0, size*sizeof(int));
	s->sp = s->stack;
	s->value = value;

	return s;
}

