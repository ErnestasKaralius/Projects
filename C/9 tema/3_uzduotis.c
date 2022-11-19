#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STACK_LENGTH 100

typedef struct Point {
    double x, y;
} Point;

typedef struct Stack {
    Point* array;
    int size;

} Stack;

void printPoint(Point p)
{
    printf("x = %f y = %f\n", p.x, p.y);
}

Point createPoint(double x, double y)
{
    return (Point){x, y};
}

double getDistance(Point a, Point b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void initStack(Stack* stack)
{
    stack->array = malloc(STACK_LENGTH * sizeof(Point));

    for(int i = 0; i < STACK_LENGTH; ++i)
         stack->array[i] = createPoint(0, 0);

    stack->size = 0;
}

void printStack(Stack* stack)
{
    for(int i = 0; i < stack->size; ++i)
    {
        printPoint(stack->array[i]);
        printf("%f\n", getDistance(stack->array[i], stack->array[0]));
    }
}

int getStackSize(Stack* stack)
{
    return stack->size;
}

void push(Stack* stack, Point value)
{
    if(getStackSize(stack) >= STACK_LENGTH)
        return;

    stack->array[getStackSize(stack)] = value;
    ++(stack->size);
}

Point top(Stack* stack)
{
    return getStackSize(stack) == 0 ? createPoint(0, 0) : stack->array[getStackSize(stack) - 1];
}

Point pop(Stack* stack)
{
    Point last_element = top(stack);

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

    for(int i = 0; i < 5; ++i)
        push(&s, createPoint(i + 1, i));

    printStack(&s);

    destroyStack(&s);

    return 0;
}
