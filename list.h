#ifndef LIST_H
#define LIST_H

struct list {
    struct list_node* head;
    struct list_node* tail;

    unsigned int count;
};

struct list_node {
    void* value;

    struct list_node* next;
    struct list_node* prev;
};

struct list* list_create();
struct list_node* list_node_create();
void list_add_back(struct list* list, void* value);
void list_remove(struct list* list, struct list_node* node);
struct list_node* list_find(struct list* list, void* value);

#endif // LIST_H
