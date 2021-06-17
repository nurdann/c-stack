#include <stdio.h>
#include "stack.h"
#include <stdlib.h> 
void printChar(Item *arr, size_t len) {
  for(int i=0; i<len; i++) {
	printf("%c, ", arr[i].c);
  }
  printf("\n");
}

char closedToOpen(char closingPair) {
  switch(closingPair) {
  case ']': return '[';
  case '}': return '{';
  case ')': return '(';
  }

  return '\0';
}

int isIn(char pair, char *pairs) {
  for(char *p = pairs; *p; p++) {
	if(pair == *p) { return 1; }
  }
  return 0;
}

int hasValidPairs(Stack *stack, char *expression) {
  for(char *c = expression; *c; c++ ) {
	if(!isIn(*c, "([{}])")) { // skip non-pair characters
	  continue;
	} else if(isIn(*c, "([{")) { // push to stack the opening pair
	  pushChar(stack, *c);
	} else if(stack->length && topChar(stack) == closedToOpen(*c)) { // pop the opening pair when its closing pair is encountered
	  pop(stack);
	} else {
	  return 0;
	}
  }

  int len = stack->length;
  free(stack->bottom);
  return len == 0;
}

int main(int argc, char* argv[]) {
  if(argc == 1) {
	fprintf(stderr, "Expected an argument\n");
	exit(1);
  }
  
  Stack stack = StackDefault;
  if(hasValidPairs(&stack, argv[1])) {
	printf("%s has properly enclosed pairs\n", argv[1]);
  } else {
	printf("%s has at least one invalid pair\n", argv[1]);
  }
  return 0;
}
