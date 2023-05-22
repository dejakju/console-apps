#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define STACK_LENGTH 5
#define EMPTY (-1)
#define STACK_EMPTY INT_MIN

typedef struct {
    int values[STACK_LENGTH];
    int top;
} stack;


bool push(stack *mystack, int value)
{
    if (mystack->top >= STACK_LENGTH - 1) return false;

    mystack->top++;
    mystack->values[mystack->top] = value;
    return true;
}

int pop(stack *mystack)
{
    if (mystack->top == EMPTY) return STACK_EMPTY;

    int result = mystack->values[mystack->top];
    mystack->top--;
    return result;
}

int main()
{
    stack s1, s2, s3;
    s1.top = EMPTY; s2.top = EMPTY; s3.top = EMPTY;

    push(&s1, 55);
    push(&s2, 42);
    push(&s2, 24);
    push(&s2, 13);
    push(&s2, 2520);
    push(&s3, 13);

    int t;
    while ((t = pop(&s2)) != STACK_EMPTY)
    {
        printf("t = %d\n", t);
    }
}