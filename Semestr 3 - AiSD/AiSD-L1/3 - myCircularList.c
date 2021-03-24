#include <stdio.h> //printf
#include <stdlib.h> //malloc, free
#include <time.h> //time in rand

// DATA TYPE

typedef struct Data Data;
struct Data {
    int value;
};

// NODE DEFINITION

typedef struct Node Node;
Node* newNode(Data data);
void node_push(Node* node, Node* new_node);

struct Node {
    Node* prev;
    Data data;
    Node* next;

    void (*push)(Node* node, Node* new_node);
};

Node* newNode(Data data) {
    Node* node_instance;
    if ((node_instance = malloc(sizeof* node_instance))) {

        node_instance->prev = NULL;
        node_instance->data = data;
        node_instance->next = NULL;
        node_instance->push = node_push;

        return node_instance;
    }
    printf("   WARNING : Lack of memory to create new Node");
    return NULL;
}

void node_push(Node* node, Node* new_node) {
    if (node->next == NULL) {
        node->next = new_node;
        new_node->prev = node;
        return;
    } else {
        node_push(node->next, new_node);
    }
}

// LIST DEFINITION

typedef struct CircularList CircularList;
CircularList* newList();
void list_push(CircularList* list, Data data);
Node* list_get_node(CircularList* list, int position);
Node* list_get_node_counted(CircularList* list, int position, int* move_times, int* comp_times);
void list_merge(CircularList* list1, CircularList* list2);
void list_delete(CircularList* list, int position);

struct CircularList {
    Node* head;

    void (*push)(CircularList* list, Data data);
    void (*merge)(CircularList* list1, CircularList* list2);
    void (*delete)(CircularList* list, int position);
    Node* (*getNode)(CircularList* list1, int position);
    Node* (*getNodeCounted)(CircularList* list1, int position, int* move_times, int* comp_times);
};

CircularList* newList() {
    CircularList* list_instance;
    if ((list_instance = malloc(sizeof* list_instance))) {

        list_instance->head = NULL;
        list_instance->push = list_push;
        list_instance->delete = list_delete;
        list_instance->merge = list_merge;
        list_instance->getNode = list_get_node;
        list_instance->getNodeCounted = list_get_node_counted;

        return list_instance;
    }
    printf("   WARNING : Lack of memory to create new CircularList");
    return NULL;
}

void list_push(CircularList* list, Data data) {
    Node* new_node = newNode(data);

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        list->head->prev->next = NULL;
        list->head->push(list->head->prev, new_node);
    }
    list->head->prev = new_node;
    new_node->next = list->head;
}

Node* list_get_node(CircularList* list, int position) {
    Node* current_node = list->head;
    while (position > 1 && current_node) {
        current_node = current_node->next;
        position--;
    }
    if (!current_node) {
        printf("   WARNING : Index out of list size");
        return NULL;
    }
    return current_node;
}

Node* list_get_node_counted(CircularList* list, int position, int* move_times, int* comp_times) {
    Node* current_node = list->head;
    while (position > 1 && current_node) {
        current_node = current_node->next;
        position--;
    }
    if (!current_node) {
        printf("   WARNING : Index out of list size");
        return NULL;
    }
    return current_node;
}

void list_delete(CircularList* list, int position) {
    Node* current_node = list->head;
    while (position > 2 && current_node) {
        current_node = current_node->next;
        position--;
    }
    if (!current_node || !current_node->next) {
        printf("   WARNING : Index out of list size");
        return;
    }
    current_node->next = current_node->next->next;
    current_node->next->prev = current_node;
}

void list_merge(CircularList* list1, CircularList* list2) {
    list1->head->prev->next = list2->head;
    list2->head->prev->next = list1->head;
    Node* tmp = list1->head->prev;
    list1->head->prev = list2->head->prev;
    list2->head->prev = tmp;
    free(list2);
}

// TESTING CIRCULAR LIST

void testLIST(CircularList* myLIST, int insertions);
void printLIST(CircularList* myLIST);
void printLISTb(CircularList* myLIST);

int main() {
    srand(time(NULL));
    {
        CircularList* myLIST = newList();
        testLIST(myLIST, 1000);

        int positions[5] = {100, 400, 600, 900, 0};
        positions[4] = rand() % 1000;

        for (int i = 0; i < 5; ++i) {
            double time = 0.0;
            int position = positions[i];
            struct timespec start, end;
            struct Node* node;

            for (int j = 0; j < 40; ++j) {
                node = myLIST->getNode(myLIST, position);
            }
            time /= 40;
            if (node) { printf("Elapsed time : %fs, Position : %d [%d]\n", time, position, node->data.value); }
        }
    }

    {
        CircularList* myLIST = newList();
        testLIST(myLIST, 6);
        CircularList* myLIST2 = newList();
        testLIST(myLIST2, 8);
        myLIST->merge(myLIST, myLIST2);
        printLIST(myLIST);
        printLISTb(myLIST);
    }

    return 0;
}

void testLIST(CircularList* myLIST, int insertions) {

    printf("\nInserting data:\n");
    for (int i = 1; i <= insertions; ++i) {
        Data data = {rand() % insertions};
        printf("%d : %d - insertion started ", i, data.value);
        myLIST->push(myLIST, data);
        printf("; ended\n");
    }

}

void printLIST(CircularList* myLIST) {
    printf("\n--------------------------\nMemory :-");
    Node* current_node = myLIST->head;
    do {
        printf(": %d ", current_node->data.value);
        current_node = current_node->next;
    } while (current_node != myLIST->head);

    printf("\n--------------------------\n");
}

void printLISTb(CircularList* myLIST) {
    printf("\n--------------------------\nMemory (b) :-");
    Node* current_node = myLIST->head->prev;
    do {
        printf(": %d ", current_node->data.value);
        current_node = current_node->prev;
    } while (current_node != myLIST->head->prev);

    printf("\n--------------------------\n");
}