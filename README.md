# Stack implemention in C

We can define struct as a stack so that it can hold the array of elements and its length as follows,

```c
struct Stack {
  size_t length; 
  union Item *bottom;
} StackDefault = {.length = 0, .bottom = NULL};
```

The union is used to allow for storing multiple types. The downside is that the size of union is the size of its largest member, but only one member is initialized.

```c
union Item {
  int d;
  char c;
  char *s;
  float f;
};
```

We will make use of `realloc` function which allocates based on stack length. When expanding, the old memory region is retained so it only looks for a new memory allocation. While shrinking, `realloc` is very efficient because it simply reduces the allocated memory region.

```c
stack->bottom = realloc(stack->bottom, (stack->length + 1) * sizeof(*stack->bottom));
```


Next, we implement multiple functions with different names for pushing an element into stack because C does not have type templating as in C++. So, we define functions such as `pushInt, pushChar, pushString, topInt, topChar...`. Since `char *` can be of variable length, the pointer is copied instead of its pointing value so the `char *` should not be freed outside of stack.


## Stack usage

Now, let us try to solve the problem of determing whether a string has proper enclosing of matching pairs of `()`, `{}` and `[]`.

We initialize stack with the default `struct`,

```c
Stack stack = StackDefault;
```

The stack has following operations that we will need,

```
pushChar(stack, *c);
char top = popChar(stack);
char top = topChar(stack);
```


We make a helper function to determine if a character is an opening pair,

```c
int isIn(char pair, char *pairs) {
  for(char *p = pairs; *p; p++) {
	if(pair == *p) { return 1; }
  }
  return 0;
}
```

We also need to be able to map the closing to its opening pair character,

``` c
char closedToOpen(char closingPair) {
  switch(closingPair) {
  case ']': return '[';
  case '}': return '{';
  case ')': return '(';
  }

  return '\0';
}
```

So now we are ready to implement the algorithm. We skip non-pair characters, then push to stack the opening pair and pop it only if current character is its closing pair. Otherwise, it is not a balanced expression. At the end, we need to free leftover stack memory and check if its size is greater than 0, which means that some pairs were not matched.

``` c
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
```

We can combine implemention of header file with main file either with `-c` flag which produces object code `.o` files,

```shell
$ gcc -c main.c stack.c
$ gcc -o x -g main.o stack.o
$ ./x '([)'
([) has at least one invalid pair
```

Or do them in one go by simply passing `.c` files to `gcc`,

```shell
$ gcc -o x main.c stack.c
$ ./x '(power())'
(power()) has properly enclosed pairs
```
