// Copyright 2022 Prunescu Bogdan-Andrei
#ifndef DECKFUNCTIONS_H_
#define DECKFUNCTIONS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DoubleLinkedList.h"

int check_deck_index(int x, int start, int end);

void remove_nth_deck(dl_list *decks, int n);

void add_deck(dl_list *decks, int nr_cards);

void add_cards(dl_list *decks, int index_deck, int nr_cards);

void delete_deck(dl_list *decks, int index_deck);

void delete_card(dl_list *decks, int index_deck, int index_card);

void deck_lengh(dl_list *decks, int index_deck);

void shuffle_deck(dl_list *decks, int index_deck);

void merge_decks(dl_list *decks, int index1, int index2);

void reverse_deck(dl_list *decks, int index_deck);

void split_deck(dl_list *decks, int index_deck, int index_split);

void sort_deck(dl_list *decks, int index_deck);

void show_deck(dl_list *decks, int index_deck);

void show_all(dl_list *decks);

void free_all(dl_list** p_deck);

#endif  // DECKFUNCTIONS_H_
