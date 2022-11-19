#include <stdio.h>
#include <stdlib.h>

#define STACK_LENGTH 100

typedef struct Stack {
    int* array;
    int size;

} Stack;

void initStack(Stack* stack)
{
    stack->array = malloc(STACK_LENGTH * sizeof(int));

    for(int i = 0; i < STACK_LENGTH; ++i)
        stack->array[i] = 0;

    stack->size = 0;
}

void printStack(Stack* stack)
{
    for(int i = 0; i < stack->size; ++i)
        printf("%d ", stack->array[i]);
}

int getStackSize(Stack* stack)
{
    return stack->size;
}

void push(Stack* stack, int value)
{
    if(getStackSize(stack) >= STACK_LENGTH)
        return;

    stack->array[getStackSize(stack)] = value;
    ++(stack->size);
}

int top(Stack* stack)
{
    return getStackSize(stack) == 0 ? 0 : stack->array[getStackSize(stack) - 1];
}

int pop(Stack* stack)
{
    int last_element = top(stack);

    if(getStackSize(stack) != 0)
        --(stack->size);

    return last_element;
}

void destroyStack(Stack* stack)
{
    free(stack->array);
    stack->size = 0;
}

int main()
{
    Stack s;
    initStack(&s);

    push(&s, 10);
    pop(&s);

    printStack(&s);
    destroyStack(&s);

    return 0;
}
