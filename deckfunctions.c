// Copyright 2022 Prunescu Bogdan-Andrei
#include "deckfunctions.h"

// Function checks if the deck index "x" exists,
// else an error message is shown.
int check_deck_index(int x, int start, int end)
{
    if (x >= start && x <= end)
        return 1;
    printf("The provided index is out of bounds for the deck list.\n");
    return 0;
}

// Function checks if the card index "x" exists,
// else an error message is shown.
int check_card_index(int x, int start, int end, int index_deck)
{
    if (x >= start && x <= end)
        return 1;
    printf("The provided index is out of bounds for deck %d.\n", index_deck);
    return 0;
}

// Function that checks if a card symbol is valid
// It returns 1 if so and 0 if the symbol is not valid
int check_symbol(char *symbol)
{
    if (strcmp(symbol, "HEART") == 0)
        return 1;
    else if (strcmp(symbol, "CLUB") == 0)
        return 1;
    else if (strcmp(symbol, "SPADE") == 0)
        return 1;
    else if (strcmp(symbol, "DIAMOND") == 0)
        return 1;
    return 0;
}

// Function that creates a card
card create_card(const int number, char *card_symbol)
{
    card tmp;
    tmp.number = number;
    strcpy(tmp.card_symbol, card_symbol);
    return tmp;
}

// Function that prints a card according to the model
void
print_card(card *card)
{
    printf("\t%d %s\n", card->number, card->card_symbol);
}

// Function that prints a deck
void
print_deck(dl_list* list)
{
    node *curr_card = list->head;
    while (curr_card != NULL) {
        card *Card = ((card *) curr_card->data);
        print_card(Card);
        curr_card = curr_card->next;
    }
}

// Function that gets the n-th deck from memory and returns a pointer to it.
dl_list*
get_nth_deck(dl_list *decks, int n)
{
    return ((dl_list *) get_nth_node(decks, n)->data);
}

// Function that frees all memory allocated for the program to run.
void free_all(dl_list** p_deck)
{
    node *curr_deck = (*p_deck)->head;
    while (curr_deck != NULL) {
        node *tmp = curr_deck;
        curr_deck = curr_deck->next;

        // First, it must free all the decks
        dl_list *tmp_deck = ((dl_list *) tmp->data);
        free_list(&tmp_deck);
        free(tmp);
    }
    free(*p_deck);
}

// Function that removes the n-th deck from memory
void remove_nth_deck(dl_list *decks, int n)
{
    node *removed = remove_nth_node(decks, n);
    dl_list *removed_deck = (dl_list *) (removed->data);
    free_list(&removed_deck);
    free(removed);
}

// Add a deck into memory
void add_deck(dl_list *decks, int nr_cards)
{
    dl_list *deck = create_list(sizeof(card));
    card card;
    char card_info[51];
    char *p;
    for (int i = 0; i < nr_cards; i++) {
        // The function reads cards line by line, then it gets the value
        // and the symbol from the line
        fgets(card_info, 50, stdin);
        card_info[strlen(card_info) - 1] = '\0';
        p = strtok(card_info, " ");
        card.number = atoi(p);
        p = strtok(NULL, " ");
        strcpy(card.card_symbol, p);

        // verifiy if it is a valid card
        if (card.number >= 1 && card.number <= 14) {
            if (check_symbol(card.card_symbol)) {
                add_nth_node(deck, deck->size, &card);
            } else {
                i--;
                printf("The provided card is not a valid one.\n");
            }
        } else {
            i--;
            printf("The provided card is not a valid one.\n");
        }
    }

    add_nth_node(decks, decks->size, deck);
    free(deck);
    printf("The deck was successfully created with %d cards.\n", nr_cards);
}


// Delete a deck from memory
void delete_deck(dl_list *decks, int index_deck)
{
    remove_nth_deck(decks, index_deck);
    printf("The deck %d was successfully deleted.\n", index_deck);
}

// Delete a card at index_card from a deck at index_deck
void delete_card(dl_list *decks, int index_deck, int index_card)
{
    dl_list *deck = get_nth_deck(decks, index_deck);
    // Check if the index is valid
    if (check_card_index(index_card, 0, deck->size - 1, index_deck) == 0)
        return;

    node *removed_card = remove_nth_node(deck, index_card);
    free(removed_card->data);
    free(removed_card);
    if (deck->size == 0)
        remove_nth_deck(decks, index_deck);
    printf("The card was successfully deleted from deck %d.\n", index_deck);
}

// Add 'nr_cards' cards to a deck at index_deck
void add_cards(dl_list *decks, int index_deck, int nr_cards)
{
    dl_list *deck = get_nth_deck(decks, index_deck);
    card card;
    char card_info[51];
    char *p;
    for (int i = 0; i < nr_cards; i++) {
        // Reads cards line by line
        fgets(card_info, 50, stdin);
        card_info[strlen(card_info) - 1] = '\0';
        p = strtok(card_info, " ");
        card.number = atoi(p);
        p = strtok(NULL, " ");
        strcpy(card.card_symbol, p);
        if (card.number >= 1 && card.number <= 14) {
            if (check_symbol(card.card_symbol)) {
                add_nth_node(deck, deck->size, &card);
            } else {
                i--;
                printf("The provided card is not a valid one.\n");
            }
        } else {
            i--;
            printf("The provided card is not a valid one.\n");
        }
    }
    printf("The cards were successfully added to deck %d.\n", index_deck);
}

// Function prints the lengh of a deck at index_deck
void deck_lengh(dl_list *decks, int index_deck)
{
    dl_list *deck = get_nth_deck(decks, index_deck);
    printf("The length of deck %d is %d.\n", index_deck, deck->size);
}


// Shuffle a deck at index_deck from the middle of it
void shuffle_deck(dl_list *decks, int index_deck)
{
    dl_list *deck = get_nth_deck(decks, index_deck);
    if (index_deck < decks->size && index_deck >= 0) {
        int mid = deck->size / 2;
        // Removes the first mid nodes at add them to the back of the list
        for (int i = 0; i < mid; i++) {
            node *moved = remove_nth_node(deck, 0);
            add_nth_node(deck, deck->size, moved->data);
            free(moved->data);
            free(moved);
        }
        printf("The deck %d was successfully shuffled.\n", index_deck);
    } else {
        printf("The provided index is out of bounds for the deck list.\n");
    }
}

// Merge two decks into a new one that is added at the end of the list
void merge_decks(dl_list *decks, int index1, int index2)
{
    dl_list *new_list = create_list(sizeof(card));
    dl_list *list1 = get_nth_deck(decks, index1);
    dl_list *list2 = get_nth_deck(decks, index2);
    node *curr1 = list1->head;
    node *curr2 = list2->head;

    // Add cards one by one from both decks
    while (curr1 != NULL && curr2 != NULL) {
        add_nth_node(new_list, new_list->size, curr1->data);
        add_nth_node(new_list, new_list->size, curr2->data);
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    // Add remaining cards
    while (curr1 != NULL) {
        add_nth_node(new_list, new_list->size, curr1->data);
        curr1 = curr1->next;
    }

    while (curr2 != NULL) {
        add_nth_node(new_list, new_list->size, curr2->data);
        curr2 = curr2->next;
    }

    printf("The deck %d and the deck %d were successfully merged.\n",
     index1, index2);

    if (index1 > index2) {
        int aux = index1;
        index1 = index2;
        index2 = aux;
    }
    remove_nth_deck(decks, index1);
    remove_nth_deck(decks, index2 - 1);
    add_nth_node(decks, decks->size, new_list);
    free(new_list);
}

// Reverse a deck at index_deck
void reverse_deck(dl_list *decks, int index_deck)
{
    dl_list *deck = get_nth_deck(decks, index_deck);
    node *curr = deck->head, *next = NULL, *prev = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        curr->prev = next;
        prev = curr;
        curr = next;
    }
    deck->head = prev;
    printf("The deck %d was successfully reversed.\n", index_deck);
}

// Splits a deck into two decks
// The first deck has cards 0 -- index_split - 1
// The second deck has cards index_split -- deck->size - 1
void split_deck(dl_list *decks, int index_deck, int index_split)
{
    dl_list *deck = get_nth_deck(decks, index_deck);
    if (check_card_index(index_split, 0, deck->size - 1, index_deck) == 0)
        return;

    dl_list *new_list = create_list(sizeof(card));
    node *curr = deck->head;
    int cnt = index_split;

    // Go to the index_split-th node
    while (cnt && curr != NULL) {
        cnt--;
        curr = curr->next;
    }

    // Add the remaining nodes inside a new list
    if (index_split != 0 && curr != NULL) {
        while (curr != NULL) {
            node *tmp = curr->next;
            add_nth_node(new_list, new_list->size, curr->data);
            remove_nth_node(deck, index_split);
            free(curr->data);
            free(curr);
            curr = tmp;
        }
        add_nth_node(decks, index_deck + 1, new_list);
    }

    free(new_list);
    printf("The deck %d was successfully split by index %d.\n",
     index_deck, index_split);
}

/*
 *  Function that compares two card_type variables.
 *  It returns:
 *  1 if x > y,
 *  -1 if x < y 
 *  0 if x = y
 */
int compare_cards(card *x, card *y) {
    if (x->number > y->number)
        return 1;
    if (x->number < y->number)
        return -1;
    if (x->number == y->number) {
        if (strcmp(x->card_symbol, "HEART") == 0) {
            if (strcmp(y->card_symbol, "HEART") == 0)
                return 0;
            return -1;
        } else if (strcmp(x->card_symbol, "SPADE") == 0) {
            if (strcmp(y->card_symbol, "HEART") == 0)
                return 1;
            if (strcmp(y->card_symbol, "SPADE") == 0)
                return 0;
            return -1;
        } else if (strcmp(x->card_symbol, "DIAMOND") == 0) {
            if (strcmp(y->card_symbol, "HEART") == 0)
                return 1;
            if (strcmp(y->card_symbol, "SPADE") == 0)
                return 1;
            if (strcmp(y->card_symbol, "DIAMOND") == 0)
                return 0;
            return -1;
        } else if (strcmp(x->card_symbol, "CLUB") == 0) {
            if (strcmp(y->card_symbol, "CLUB") == 0)
                return 0;
            return 1;
        }
    }
    return 0;
}

// Sorts a deck by value and by symbol if the values of two cards are equal
void sort_deck(dl_list *decks, int index_deck)
{
    dl_list *deck = get_nth_deck(decks, index_deck);
    node *slow_pr = deck->head;
    node *fast_pr = slow_pr->next;
    while (slow_pr->next != NULL) {
        fast_pr = slow_pr->next;
        while (fast_pr != NULL) {
            card *x = (card *) slow_pr->data;
            card *y = (card *) fast_pr->data;
            if (compare_cards(x, y) > 0) {
                slow_pr->data = (void *) y;
                fast_pr->data = (void *) x;
            }
            fast_pr = fast_pr->next;
        }
        slow_pr = slow_pr->next;
    }
    printf("The deck %d was successfully sorted.\n", index_deck);
}

// Prints a deck at index_deck
void show_deck(dl_list *decks, int index_deck)
{
    if (index_deck < decks->size && index_deck >= 0) {
        dl_list *deck = (dl_list *) get_nth_node(decks, index_deck)->data;
        printf("Deck %d:\n", index_deck);
        print_deck(deck);
    } else {
        printf("The provided index is out of bounds for the deck list.\n");
    }
}

// Print all the decks from memory
void show_all(dl_list *decks)
{
    node *curr_deck = decks->head;
    int index_deck = 0;
    while (curr_deck != NULL) {
        printf("Deck %d:\n", index_deck);
        dl_list *deck = ((dl_list *) curr_deck->data);
        print_deck(deck);
        index_deck++;
        curr_deck = curr_deck->next;
    }
}
