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
void node_push(Node* node, Data data);

struct Node {
    Data data;
    Node* next;

    void (*addChild)(Node* node, Data data);
};

Node* newNode(Data data) {
    Node* node_instance;
    if ((node_instance = malloc(sizeof* node_instance))) {

        node_instance->data = data;
        node_instance->next = NULL;
        node_instance->addChild = node_push;

        return node_instance;
    }
    printf("   WARNING : Lack of memory to create new Node");
    return NULL;
}

void node_push(Node* node, Data data) {
    if (node->next == NULL) {
        node->next = newNode(data);
        return;
    } else {
        node_push(node->next, data);
    }
}

// LIST DEFINITION

typedef struct List List;
List* newList();
void list_push(List* list, Data data);
void list_delete(List* list, int position);
Node* list_get_node(List* list, int position);
Node* list_get_node_counted(List* list, int position, int* move_times, int* comp_times);
void list_merge(List* list1, List* list2);

struct List {
    Node* head;

    void (*push)(List* list, Data data);
    void (*merge)(List* list1, List* list2);
    void (*delete)(List* list, int position);
    Node* (*getNode)(List* list, int position);
    Node* (*getNodeCounted)(List* list1, int position, int* move_times, int* comp_times);
};

List* newList() {
    List* list_instance;
    if ((list_instance = malloc(sizeof* list_instance))) {

        list_instance->head = NULL;
        list_instance->push = list_push;
        list_instance->merge = list_merge;
        list_instance->delete = list_delete;
        list_instance->getNode = list_get_node;
        list_instance->getNodeCounted = list_get_node_counted;

        return list_instance;
    }
    printf("   WARNING : Lack of memory to create new List");
    return NULL;
}

void list_push(List* list, Data data) {
    if (list->head == NULL) {
        list->head = newNode(data);
    } else {
        list->head->addChild(list->head, data);
    }
}

Node* list_get_node(List* list, int position) {
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

Node* list_get_node_counted(List* list, int position, int* move_times, int* comp_times) {
    (*move_times)++;
    Node* current_node = list->head;
    while (position > 1) {
        (*comp_times)++;
        if (!current_node) {
            printf("   WARNING : Index out of list size");
            return NULL;
        }
        (*move_times)++;
        current_node = current_node->next;
        position--;
    }

    return current_node;
}

void list_delete(List* list, int position) {
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
}

void list_merge(List* list1, List* list2) {
    Node* current_node = list1->head;
    while (current_node->next) {
        current_node = current_node->next;
    }
    current_node->next = list2->head;
    free(list2);
}

// TESTING LIST

void testLIST(List* myLIST, int insertions);
void printLIST(List* myLIST);

int main() {
    srand(time(NULL));
    {
        List* myLIST = newList();
        testLIST(myLIST, 1000);

        int positions[5] = {100, 400, 600, 900, 0};

        for (int i = 0; i < 5; ++i) {
            int position = positions[i];
            Node* node = NULL;
            int comp_num = 0;
            int move_num = 0;
            int cycles = 100;
            int log = 1;

            for (int j = 0; j < cycles; ++j) {
                if (i == 4) { position = rand() % 1000; if (log) { printf("%d;", position); if (j % 25 == 24) { printf("\n"); } } }
                node = myLIST->getNodeCounted(myLIST, position, &move_num, &comp_num);
            }
            double comp_avg = (double) comp_num / cycles;
            double move_avg = (double) move_num / cycles;
            if (node && i != 4) { printf("Moves: %.1f; Compares: %.1f; Position : %d [%d]\n", move_avg, comp_avg, position, node->data.value); }
            else if (node) { printf("Moves avg: %.1f; Compares avg: %.1f; Position : randomized < 1000\nMoves total: %d; Compares total: %d\n", move_avg, comp_avg, move_num, comp_num); }
        }
    }

    {
        List* myLIST = newList();
        testLIST(myLIST, 6);
        List* myLIST2 = newList();
        testLIST(myLIST2, 8);
        myLIST->merge(myLIST, myLIST2);
        printLIST(myLIST);
    }

    return 0;
}

void testLIST(List* myLIST, int insertions) {

    printf("\nInserting data:\n");
    for (int i = 1; i <= insertions; ++i) {
        Data data = {rand() % insertions};
        printf("%d : %d - insertion started ", i, data.value);
        myLIST->push(myLIST, data);
        printf("; ended\n");
    }

}

void printLIST(List* myLIST) {
    printf("\n--------------------------\nMemory :-");
    Node* current_node = myLIST->head;
    while (current_node) {
        printf(": %d ", current_node->data.value);
        current_node = current_node->next;
    }
    printf("\n--------------------------\n");
}