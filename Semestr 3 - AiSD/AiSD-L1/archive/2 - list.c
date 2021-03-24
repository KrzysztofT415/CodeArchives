#include <stdio.h> //printf
#include <stdlib.h> //random, malloc
#include <time.h> //clock

struct my_node {
    int value;
    struct my_node *next;
};
struct my_list {
    struct my_node *root;
};

void NODE_PUSH(struct my_node *node, struct my_node *new_node) {
    if (node->next == NULL) {
        node->next = new_node;
        return;
    } else {
        NODE_PUSH(node->next, new_node);
    }
}

void LIST_PUSH(struct my_list *list, int value) {
    struct my_node *node;
    node = malloc(sizeof(struct my_node));
    node->next = NULL;
    node->value = value;

    if (list->root == NULL) {
        list->root = node;
    } else {
        NODE_PUSH(list->root, node);
    }
}

struct my_node* LIST_GET(struct my_node *node, int *position) {
    if (*position == 1) { return &*node; }
    (*position)--;
    if (node->next == NULL) {
        printf("Index out of bounds");
        return NULL;
    }
    return LIST_GET(node->next, position);
}

struct my_node* LISTS_MERGE(struct my_list *list1, struct my_list *list2) {
    struct my_node *last = list1->root;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = list2->root;

}

int main() {
    {
        srand(time(NULL));

        //CREATING LIST
        struct my_list list;
        list.root = NULL;

        for (int i = 0; i < 1000; ++i) {
            int value = rand() % 1000;
            LIST_PUSH(&list, value);
        }

        //TESTING ACCESS TIME
        int positions[5] = {100, 400, 600, 900, 0};
        positions[4] = rand() % 1000;

        for (int i = 0; i < 5; ++i) {
            double time = 0.0;
            int position = positions[i];
            struct timespec start, end;
            struct my_node *node;

            for (int j = 0; j < 40; ++j) {

//            clock_gettime(CLOCK_REALTIME, &start);
                node = LIST_GET(list.root, &position);
//            clock_gettime(CLOCK_REALTIME, &end);
//
//            time_t t1ns = start.tv_nsec/1E6;
//            time_t t1s = start.tv_sec;
//            time_t t2ns = end.tv_nsec/1E6;
//            time_t t2s = end.tv_sec;
//            time += (t2s - t1s) + (t2ns - t1ns) * 1E-3;
                position = positions[i];
            }
            time /= 40;
            printf("Elapsed time : %fs, Position : %d [%d]\n", time, positions[i],
                   LIST_GET(list.root, &position)->value);
        }
    }
    {
        struct my_list list1;
        list1.root = NULL;
        struct my_list list2;
        list2.root = NULL;

        for (int i = 0; i < 8; ++i) {
            LIST_PUSH(&list1, i + 1);
        }
        for (int i = 0; i < 5; ++i) {
            LIST_PUSH(&list2, i + 1);
        }
        LISTS_MERGE(&list1, &list2);

        struct my_node *last = list1.root;
        while (last->next != NULL) {
            printf("%d, ", last->value);
            last = last->next;
        }
        printf("%d\n", last->value);
    }
    return 0;
}