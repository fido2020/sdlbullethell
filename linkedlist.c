#include <stdlib.h>
#include <stdio.h>

struct list {
    struct list_node* head;
    struct list_node* tail;

    unsigned int count;
};

struct list_node {
    int value;

    struct list_node* next;
    struct list_node* prev;
};

struct list* list_create() {
    struct list* l = (struct list*)malloc(sizeof(struct list));

    l->count = 0;
    l->head = NULL;
    l->tail = NULL;

    return l;
}

struct list_node* list_node_create() {
    struct list_node* node = (struct list_node*)malloc(sizeof(struct list_node));

    node->next = NULL;
    node->prev = NULL;

    return node;
}

void list_add_back(struct list* list, int value) {
    struct list_node* node = list_node_create();
    if(list->tail) { // Case 1: List is not empty
        // The old tail points to our new node in the list
        node->prev = list->tail;
        list->tail->next = node;

        // The new node becomes the tail
        list->tail = node;
    } else { // Case 2: List is empty
        // Since the new node will be the only item in the list,
        // it becomes the new head AND tail.
        list->head = node;
        list->tail = node;
    }

    node->value = value;

    // Add 1 to the number of items in the list
    list->count++;
}

void list_remove(struct list* list, struct list_node* node) {
    if(list->head == node) { // Node to remove is the head
        list->head = node->next;
    }

    if(list->tail == node) { // Node to remove is the tail
        list->tail = node->prev;
    }

    // Ok so now we have to make it so the node BEFORE the one being removed
    // points to the one AFTER the one being removed
    if(node->next) {
        node->next->prev = node->prev;
    }

    // AND make it so the node BEFORE points to the one AFTER
    if(node->prev) {
        node->prev->next = node->next;
    }

    list->count--;
}

// This function finds the FIRST occurance of value in the list
struct list_node* list_find(struct list* list, int value) {
    for(struct list_node* node = list->head; node != NULL; node = node->next) {
        if(node->value == value) {
            return node;
        }
    }

    // No item in list with the right value
    return NULL;
}

void list_print(struct list* list) {
    printf("List contents (%i items): ", list->count);

    for(struct list_node* node = list->head; node != NULL; node = node->next) {
        printf("%i ", node->value);
    }

    printf("\n");
}

int main() {
    struct list* list = list_create();

    list_print(list);

    list_add_back(list, 42);
    list_add_back(list, -1);
    list_add_back(list, 4096);
    list_add_back(list, 177);
    list_add_back(list, 86);

    list_print(list);

    struct list_node* n = list_find(list, 4096);
    if(n)
        list_remove(list, n);

    list_print(list);

    n = list_find(list, 42);
    if(n)
        list_remove(list, n);

    list_print(list);

    return 0;
}
