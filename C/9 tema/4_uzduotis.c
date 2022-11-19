#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
    double x, y;
} Point;

typedef struct List {
    Point point;
    struct List* next;

} List;

void printPoint(Point p)
{
    printf("x = %f y = %f\n", p.x, p.y);
}

Point createPoint(double x, double y)
{
    return (Point){x, y};
}

List* createList(Point value)
{
    List* list = malloc(sizeof(List));
    list->point = value;
    list->next = NULL;

    return list;
}

void printList(List* list)
{
    while(list != NULL)
    {
        printPoint(list->point);
        list = list->next;
    }
}

int getListSize(List* list)
{
    int size = 0;
    while(list != NULL)
    {
        ++size;
        list = list->next;
    }

    return size;
}

void insertElement(List** list, Point value)
{
    List* new_list = malloc(sizeof(List));
    new_list->point = value;
    new_list->next = *list;

    *list = new_list;
}

Point getElement(List* list)
{
    return getListSize(list) == 0 ? createPoint(0, 0) : list->point;
}

Point deleteElement(List** list)
{
    if(getListSize(*list) == 0)
        return createPoint(0, 0);

    Point first_element = getElement(*list);
    List* old_list = *list;

    *list = (*list)->next;

    free(old_list);
    return first_element;
}

void destroyList(List** list)
{
    int list_size = getListSize(*list);
    List* next_list;

    for(int i = 0; i < list_size; ++i)
    {
        next_list = (*list)->next;
        free(list);
        *list = next_list;
    }
}

int main()
{
    List* list1 = createList(createPoint(1, 1));
    List* list2 = createList(createPoint(2, 2));
    List* list3 = createList(createPoint(3, 3));

    list1->next = list2;
    list2->next = list3;

    insertElement(&list1, createPoint(0, 0));
    printList(list1);
    printf("\n");

    destroyList(&list1);
    printList(list1);

    return 0;
}
