#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

typedef struct List {
    char** words;
    int length;
    struct List* next;
    struct List* prev;

} List;

char** create_string_array(int length)
{
    char** array = calloc(1, length * sizeof(*array));
    for(int i = 0; i < length; ++i)
        array[i] = calloc(1, MAX_STRING_LENGTH);

    return array;
}

void free_string_array(char** array, int length)
{
    for(int i = 0; i < length; ++i)
        free(array[i]);

    free(array);
}

List* createList(int length)
{
    List* list = malloc(sizeof(List));
    list->next = NULL;
    list->prev = NULL;
    list->words = create_string_array(length);
    list->length = length;

    return list;
}

void fill_arrays(List** list, char strings[][MAX_STRING_LENGTH])
{
    List* ptr = *list;

    while(ptr != NULL)
    {
        for(int i = 0; i < ptr->length; ++i)
            strcpy(ptr->words[i], strings[i]);

        ptr = ptr->next;
    }
}

void printList(List* list)
{
    while(list != NULL)
    {
        for(int i = 0; i < list->length; ++i)
            printf("%s\n", list->words[i]);

        printf("\n");
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

void swap_lists(List* first, List* second)
{
    char** temp_words = second->words;
    int temp_l = second->length;

    second->words = first->words;
    first->words = temp_words;

    second->length = first->length;
    first->length = temp_l;
}

int check_order_ascending(List first, List second)
{
    if(second.length < first.length)
        return 1;

    return 0;
}

int check_order_descending(List first, List second)
{
    if(second.length > first.length)
        return 1;

    return 0;
}

void sort_list(List** list, char order)
{
    List* first = *list;
    List* second;

    int (*order_function)(List, List) = (order == 'd') ? check_order_descending : check_order_ascending;

    while(first->next != NULL)
    {
        second = first->next;
        while(second != NULL)
        {
            if(order_function(*first, *second))
                swap_lists(first, second);

            second = second->next;
        }

        first = first->next;
    }
}

void sort_strings(char** words, int length)
{
    for(int i = 0; i < length - 1; ++i)
        for(int j = i + 1; j < length; ++j)
            if(strcmp(words[i], words[j]) > 0)
            {
                char temp[MAX_STRING_LENGTH];
                strcpy(temp, words[i]);

                strcpy(words[i], words[j]);
                strcpy(words[j], temp);
            }
}

void destroyList(List** list)
{
    int list_size = getListSize(*list);
    List* next_list;

    for(int i = 0; i < list_size; ++i)
    {
        next_list = (*list)->next;
        free_string_array((*list)->words, (*list)->length);
        free(list);
        *list = next_list;
    }
}

int main()
{
    List* list1;
    List* list2;

    char strings[][MAX_STRING_LENGTH] = {"Hello\0", "Bye\0", "Home\0", "Abc\0" "Abcdefg\0", "IIIII\0", "452\0"};

    list1 = createList(4);
    list2 = createList(1);
    list1->next = list2;
    list2->prev = list1;

    fill_arrays(&list1, strings);

    sort_list(&list1, 'd');
    sort_strings(list1->words, list1->length);
    printList(list1);

    destroyList(&list1);

    return 0;
}
