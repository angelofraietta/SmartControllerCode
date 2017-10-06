#include <iostream.h>

const int STACK_SIZE = 100;

struct stack {
  int count;
  int data[STACK_SIZE];
};
  
inline void stack_push(struct stack &the_stack, const int item) {
    the_stack.data[the_stack.count] = item;
    ++the_stack.count;
}
  
inline int stack_pop(struct stack &the_stack) {
    --the_stack.count;
    return the_stack.data[the_stack.count];  
}
  
inline void stack_init(struct stack &the_stack) {
      the_stack.count = 0;  
}

int main() {
  struct stack s;
  stack_init(s);
  int j = 0;
  for ( j = 0; j < STACK_SIZE; j++ ) {
    stack_push(s,j);
  }
  int answer = 0;
  for ( j = 0; j < STACK_SIZE; j++ ) {
    int answer = stack_pop(s);
    cout << answer << endl;
  }
}
