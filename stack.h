#ifndef STACK_H
#define STACK_H
#include <stddef.h> // size_t

// Define stack item as union because only one of its members is used
// The size of union is the size of its largest member
union Item {
  int d;
  char c;
  char *s;
  float f;
};

struct Stack {
  size_t length; 
  union Item *bottom;
};

typedef struct Stack Stack;
typedef union Item Item;
Stack StackDefault;

Item top(Stack *stack);
int topInt(Stack *stack);
char topChar(Stack *stack);
float topFloat(Stack *stack);
char* topString(Stack *stack);

void expandStack(Stack *stack);
void pushInt(Stack *stack, int item);
void pushChar(Stack *stack, char item);
void pushFloat(Stack *stack, float item);
void pushString(Stack *stack, char *item);

Item pop(Stack *stack);
int popInt(Stack *stack);
char popChar(Stack *stack);
float popFloat(Stack *stack);
char* popString(Stack *stack);


#endif
