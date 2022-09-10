// Copyright 2022 Prunescu Bogdan-Andrei
#include "DoubleLinkedList.h"

dl_list* create_list(int data_size)
{
    dl_list *tmp = malloc(sizeof(*tmp));
    tmp->data_size = data_size;
    tmp->head = NULL;
    tmp->size = 0;
    return tmp;
}

node* create_node(const void *data, size_t size)
{
    node *tmp = malloc(sizeof(*tmp));
    tmp->data = malloc(size);
    memcpy(tmp->data, data, size);
    tmp->next = NULL;
    tmp->prev = NULL;
    return tmp;
}

node*
get_nth_node(dl_list* list, int n)
{
    node *curr = list->head;
    while (n--) {
        curr = curr->next;
    }
    return curr;
}

void
add_nth_node(dl_list* list, int n, const void* data)
{
    node *new_node = create_node(data, list->data_size);

    if (list->head == NULL) {
        list->head = new_node;
        list->size++;
        return;
    }

    if (n == 0) {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
        list->size++;
        return;
    }

    node *curr = list->head;
    while (--n > 0 && curr->next != NULL) {
        curr = curr->next;
    }

    node *next = curr->next;

    curr->next = new_node;
    new_node->prev = curr;
    new_node->next = next;
    if (next != NULL)
        next->prev = new_node;

    list->size++;
}

node*
remove_nth_node(dl_list* list, int n)
{
    if (list->size == 0)
        return NULL;
    node *curr = list->head;
    int cnt = 0;
    while (cnt < list->size - 1 && n - cnt > 0) {
        curr = curr->next;
        cnt++;
    }
    node *prev = curr->prev;
    node *next = curr->next;
    if (curr == list->head)
        list->head = next;
    if (prev != NULL)
        prev->next = next;
    if (next != NULL)
        next->prev = prev;
    list->size--;

    return curr;
}

void free_list(dl_list** pp_list)
{
    node *curr = (*pp_list)->head;
    node *tmp = NULL;
    int n = (*pp_list)->size;
    for (int i = 0; i < n; i++) {
        tmp = curr;
        curr = curr->next;
        free(tmp->data);
        free(tmp);
    }
    free(*pp_list);
    *pp_list = NULL;
}
