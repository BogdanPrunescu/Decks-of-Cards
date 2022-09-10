// Copyright 2022 Prunescu Bogdan-Andrei
#ifndef DOUBLELINKEDLIST_H_
#define DOUBLELINKEDLIST_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct card {
    int number;
    char card_symbol[10];
}card;

typedef struct node {
    void *data;
    struct node *prev, *next;
}node;

typedef struct dl_list{
    node *head;
    int size;
    size_t data_size;
}dl_list;

dl_list* create_list(int data_size);

node* create_node(const void *data, size_t size);

node*
get_nth_node(dl_list* list, int n);

void
add_nth_node(dl_list* list, int n, const void* data);

node*
remove_nth_node(dl_list* list, int n);

void free_list(dl_list** pp_list);

#endif  // DOUBLELINKEDLIST_H_
