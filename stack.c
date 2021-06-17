#include "stack.h"
#include <stdlib.h> // realloc
#include <stdio.h> // fprintf

// Get last element of array that is top of stack
Item top(Stack *stack) {
  return stack->bottom[stack->length - 1];
}

// Get top of stack as a specific type
int topInt(Stack *stack) {
  return top(stack).d;
}

char topChar(Stack *stack) {
  return top(stack).c;
}

float topFloat(Stack *stack) {
  return top(stack).f;
}

char* topString(Stack *stack) {
  return top(stack).s;
}

// Increment stack by one more element size
void expandStack(Stack *stack) {
  stack->bottom = realloc(stack->bottom, (stack->length + 1) * sizeof(*stack->bottom));
  if(!stack->bottom) {
	fprintf(stderr, "Cannot find more memory in heap\n");
	free(stack->bottom);
	exit(1);
  }
  stack->length++;
}

// Push to stack by specific type
void pushInt(Stack *stack, int item) {
  expandStack(stack);
  stack->bottom[stack->length - 1].d = item;
}

void pushChar(Stack *stack, char item) {
  expandStack(stack);
  stack->bottom[stack->length - 1].c = item;
}

void pushFloat(Stack *stack, float item) {
  expandStack(stack);
  stack->bottom[stack->length - 1].f = item;
}

void pushString(Stack *stack, char *item) {
  expandStack(stack);
  stack->bottom[stack->length - 1].s = item;
}

// Pop and return the popped element
Item pop(Stack *stack) {
  if(stack->length == 0) {
	fprintf(stderr, "Cannot pop empty stack\n");
	free(stack->bottom);
	exit(1);
  }
  Item prevTop = top(stack);
  stack->bottom = realloc(stack->bottom, (stack->length - 1) * sizeof(*stack->bottom));
  stack->length--;
  return prevTop;
}

// Pop and return specific element
int popInt(Stack *stack) {
  return pop(stack).d;
}

char popChar(Stack *stack) {
  return pop(stack).c;
}

float popFloat(Stack *stack) {
  return pop(stack).f;
}

char* popString(Stack *stack) {
  return pop(stack).s;
}

Stack StackDefault = {.length = 0, .bottom = NULL};
