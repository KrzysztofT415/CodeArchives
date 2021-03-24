#include <stdio.h> //printf
#include <stdlib.h> //malloc

// DATA TYPE

typedef struct Data Data;
struct Data {
    double value;
};

// QUEUE DEFINITION

typedef struct Queue Queue;
Queue* newQueue(int MAX_SIZE);
void queue_push(Queue* queue, Data data);
Data* queue_next(Queue* queue);

struct Queue {
    int MAX_SIZE;
    int size;
    int front;
    Data* data;

    void (*push)(Queue* queue, Data data);
    Data* (*next)(Queue* queue);
};

Queue* newQueue(int MAX_SIZE) {
    Queue* queue_instance;
    if ((queue_instance = malloc(sizeof *queue_instance))
        && (queue_instance->data = malloc(MAX_SIZE * sizeof(Data)))) {

        queue_instance->MAX_SIZE = MAX_SIZE;
        queue_instance->size = 0;
        queue_instance->front = 0;
        queue_instance->next = queue_next;
        queue_instance->push = queue_push;

        return queue_instance;
    }
    printf("   WARNING : Lack of memory to create new Queue");
    return NULL;
}

void queue_push(Queue* queue, Data data) {
    if (queue->size + 1 > queue->MAX_SIZE) {
        printf("   WARNING : Queue overflow, data lost ");
        return;
    }
    queue->data[(queue->size + queue->front) % queue->MAX_SIZE] = data;
    queue->size++;
}

Data* queue_next(Queue* queue) {
    if (queue->size != 0) {
        queue->size--;
        Data* next = &queue->data[queue->front];
        queue->front++;
        if (queue->front >= queue->MAX_SIZE) {
            queue->front = 0;
        }
        return next;
    }
    printf("   WARNING : Tried to get next data from empty Queue\n");
    return NULL;
}

// TESTING QUEUE

void testFIFO();

int main() {
    {
        Queue *myFIFO = newQueue(100);

        printf("\nInserting data:\n");
        for (int i = 1; i <= 100; ++i) {
            Data data = {i * 0.5};
            myFIFO->push(myFIFO, data);
            printf("%.1f\n", data.value);
        }

        printf("\nPrinting data:\n");
        for (int i = 1; i <= 100; ++i) {
            Data *data = myFIFO->next(myFIFO);
            if (data) { printf("%.1f\n", data->value); }
        }
    }

//    testFIFO(); // uncomment this line to see how memory works
    return 0;
}

// MY TEST OF MEMORY MANAGEMENT (EXTRA)

void manageFIFO(Queue* myFIFO, int insertions, int deletions);
void printFIFO(Queue* myFIFO);

void testFIFO() {
    printf("\n\nCreating new Queue");
    Queue* myFIFO = newQueue(16);
    printFIFO(myFIFO);
    printf("Inserting 3.33\n");
    Data data = {3.33};
    myFIFO->push(myFIFO, data);
    manageFIFO(myFIFO, 1, 4);
    printFIFO(myFIFO);
    manageFIFO(myFIFO, 18, 5);
    printFIFO(myFIFO);
    printf("Inserting 1.25\n");
    Data data2 = {1.25};
    myFIFO->push(myFIFO, data2);
    printFIFO(myFIFO);
    manageFIFO(myFIFO, 5, 15);
    printFIFO(myFIFO);
    printf("Elements left : %d\n", myFIFO->size);
    printf("It is : %.1f\n--------------------\n", myFIFO->next(myFIFO)->value);
}

void manageFIFO(Queue* myFIFO, int insertions, int deletions) {
    printf("\nInserting data:\n");
    for (int i = 1; i <= insertions; ++i) {
        Data data = {i * 0.5};
        printf("%d : %.1f - insertion started ", i, data.value);
        myFIFO->push(myFIFO, data);
        printf("; ended\n");
    }

    printf("\nPrinting data:\n");
    for (int i = 1; i <= deletions; ++i) {
        Data* a = myFIFO->next(myFIFO);
        if (a) { printf("%.1f\n", a->value); }
    }
}

void printFIFO(Queue* myFIFO) {
    printf("\n--------------------------\nMemory :-");
    for (int i = 0; i < myFIFO->MAX_SIZE; ++i) {
        printf(": %.2f ", myFIFO->data[i].value);
    }
    printf("\n--------------------------\n");
}
