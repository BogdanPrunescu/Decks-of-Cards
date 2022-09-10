// Copyright 2022 Prunescu Bogdan-Andrei
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deckfunctions.h"
#include "DoubleLinkedList.h"

int main() {
    dl_list *decks = create_list(sizeof(dl_list));

    char command[101];
    char *p;
    do {
        // The program reads commands line by line
        // and interprets them using strtok
        fgets(command, 100, stdin);
        if (strcmp(command, "EXIT") != 0)
            command[strlen(command) - 1] = '\0';

        p = strtok(command, " ");

        // ADD_DECK command
        if (strcmp(p, "ADD_DECK") == 0) {
            p = strtok(NULL, " ");
            int nr_cards = atoi(p);
            p = strtok(NULL, " ");

            // Check if there are any words left after a valid command
            // and print an error if so
            if (p == NULL)
                add_deck(decks, nr_cards);
            else
                printf("Invalid command. Please try again.\n");

        // DEL_DECK command
        } else if (strcmp(p, "DEL_DECK") == 0) {
            p = strtok(NULL, " ");
            int index_deck = atoi(p);
            p = strtok(NULL, " ");

            if (p == NULL) {
                if (check_deck_index(index_deck, 0, decks->size - 1) == 1)
                    delete_deck(decks, index_deck);
            } else {
                printf("Invalid command. Please try again.\n");
            }

        // ADD_CARDS command
        } else if (strcmp(p, "ADD_CARDS") == 0) {
            p = strtok(NULL, " ");
            int index_deck = atoi(p);

            p = strtok(NULL, " ");
            int nr_cards = atoi(p);
            p = strtok(NULL, " ");

            if (p == NULL) {
                if (check_deck_index(index_deck, 0, decks->size - 1) == 1)
                    add_cards(decks, index_deck, nr_cards);
            } else {
                printf("Invalid command. Please try again.\n");
            }

        // DEL_CARD command
        } else if (strcmp(p, "DEL_CARD") == 0) {
            p = strtok(NULL, " ");
            int index_deck = atoi(p);

            p = strtok(NULL, " ");
            int index_card = atoi(p);
            p = strtok(NULL, " ");

            if (p == NULL) {
                if (check_deck_index(index_deck, 0, decks->size - 1) == 1)
                    delete_card(decks, index_deck, index_card);
            } else {
                printf("Invalid command. Please try again.\n");
            }

        // DECK_NUMBER command
        } else if (strcmp(p, "DECK_NUMBER") == 0) {
            p = strtok(NULL, " ");
            if (p == NULL)
                printf("The number of decks is %d.\n", decks->size);
            else
                printf("Invalid command. Please try again.\n");

        // DECK_LEN command
        } else if (strcmp(p, "DECK_LEN") == 0) {
            p = strtok(NULL, " ");
            int index_deck = atoi(p);
            p = strtok(NULL, " ");

            if (p == NULL) {
                if (check_deck_index(index_deck, 0, decks->size - 1) == 1)
                    deck_lengh(decks, index_deck);
            } else {
                printf("Invalid command. Please try again.\n");
            }

        // SHUFFLE_DECK command
        } else if (strcmp(p, "SHUFFLE_DECK") == 0) {
            p = strtok(NULL, " ");
            int index_deck = atoi(p);
            p = strtok(NULL, " ");

            if (p == NULL) {
                if (check_deck_index(index_deck, 0, decks->size - 1) == 1)
                    shuffle_deck(decks, index_deck);
            } else {
                printf("Invalid command. Please try again.\n");
            }

        // MERGE_DECKS command
        } else if (strcmp(p, "MERGE_DECKS") == 0) {
            p = strtok(NULL, " ");
            int index1 = atoi(p);

            p = strtok(NULL, " ");
            int index2 = atoi(p);
            p = strtok(NULL, " ");

            if (p == NULL) {
                if (check_deck_index(index1, 0, decks->size - 1))
                    if (check_deck_index(index2, 0, decks->size - 1))
                        merge_decks(decks, index1, index2);
            } else {
                printf("Invalid command. Please try again.\n");
            }

        // SPLIT_DECK command
        } else if (strcmp(p, "SPLIT_DECK") == 0) {
            p = strtok(NULL, " ");
            int index_deck = atoi(p);

            p = strtok(NULL, " ");
            int index_split = atoi(p);
            p = strtok(NULL, " ");

            if (p == NULL) {
                if (check_deck_index(index_deck, 0, decks->size - 1))
                    split_deck(decks, index_deck, index_split);
            } else {
                printf("Invalid command. Please try again.\n");
            }

        // REVERSE_DECK command
        } else if (strcmp(p, "REVERSE_DECK") == 0) {
            p = strtok(NULL, " ");
            int index_deck = atoi(p);
            p = strtok(NULL, " ");

            if (p == NULL) {
                if (check_deck_index(index_deck, 0, decks->size - 1))
                    reverse_deck(decks, index_deck);
            } else {
                printf("Invalid command. Please try again.\n");
            }

        // SHOW_DECK command
        } else if (strcmp(p, "SHOW_DECK") == 0) {
            p = strtok(NULL, " ");
            int index_deck = atoi(p);
            p = strtok(NULL, " ");

            if (p == NULL) {
                if (check_deck_index(index_deck, 0, decks->size - 1))
                    show_deck(decks, index_deck);
            } else {
                printf("Invalid command. Please try again.\n");
            }

        // SHOW_ALL command
        } else if (strcmp(p, "SHOW_ALL") == 0) {
            p = strtok(NULL, " ");
            if (p == NULL)
                show_all(decks);
            else
                printf("Invalid command. Please try again.\n");

        // SORT_DECK command
        } else if (strcmp(p, "SORT_DECK") == 0) {
            p = strtok(NULL, " ");
            int index_deck = atoi(p);
            p = strtok(NULL, " ");

            if (p == NULL) {
                if (check_deck_index(index_deck, 0, decks->size - 1))
                    sort_deck(decks, index_deck);
            } else {
                printf("Invalid command. Please try again.\n");
            }

        // other commands
        } else if (strcmp(p, "EXIT") != 0) {
            printf("Invalid command. Please try again.\n");
        }
    } while (!p || strcmp(p, "EXIT") != 0);

    free_all(&decks);
    return 0;
}
