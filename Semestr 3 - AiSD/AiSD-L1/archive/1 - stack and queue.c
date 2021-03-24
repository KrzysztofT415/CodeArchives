#include <stdio.h>
#define BUFFER_SIZE 100

void LIFO_PUSH(int *data, int *size, int value);
int* LIFO_POP(int *data, int *size);

void FIFO_PUSH(int *data, const int *front, int *size, int value);
int* FIFO_NEXT(int *data, int *front, int *size);

int main() {
    {
        printf("------------------------------\n:   STACK (LIFO) TEST   :\n");
        struct my_stack {
            int size;
            int data[BUFFER_SIZE];
        };
        struct my_stack stack;
        stack.size = 0;

        printf("INSERTING DATA\n");
        for (int i = 1; i <= 100; ++i) {
            printf("%d\n", i);
            LIFO_PUSH(stack.data, &stack.size, i);
        }

        printf("\nPRINTING DATA\n");
        for (int i = 0; i < 100; ++i) {
            int *value = LIFO_POP(stack.data, &stack.size);
            if (value != NULL) { printf("%d\n", *value); }
        }
    }

    {
        printf("------------------------------\n:   QUEUE (FIFO) TEST   :\n");
        struct my_queue {
            int front;
            int size;
            int data[BUFFER_SIZE];
        };
        struct my_queue queue;
        queue.front = 0;
        queue.size = 0;

        printf("INSERTING DATA\n");
        for (int i = 1; i <= 100; ++i) {
            printf("%d\n", i);
            FIFO_PUSH(queue.data, &queue.front, &queue.size, i);
        }

        printf("\nPRINTING DATA\n");
        for (int i = 0; i < 100; ++i) {
            int *value = FIFO_NEXT(queue.data, &queue.front, &queue.size);
            if (value != NULL) { printf("%d\n", *value); }
        }
    }

    return 0;
}

void LIFO_PUSH(int *data, int *size, int value) {
    if (*size >= BUFFER_SIZE) {
        printf("WARNING : Stack overflow\n");
        return;
    }
    data[*size] = value;
    (*size)++;
}

int* LIFO_POP(int *data, int *size) {
    if (*size == 0) {
        printf("WARNING : Tried to pop empty stack\n");
        return NULL;
    }
    (*size)--;
    return &data[*size];
}

void FIFO_PUSH(int *data, const int *front, int *size, int value) {
    if (*size + 1 > BUFFER_SIZE) {
        printf("WARNING : Queue overflow");
        return;
    }
    int place = (*size + *front) % BUFFER_SIZE;
    data[place] = value;
    (*size)++;
}

int* FIFO_NEXT(int *data, int *front, int *size) {
    if (*size == 0) {
        printf("WARNING : Tried to get next value from empty queue\n");
        return NULL;
    }
    (*size)--;
    int place = *front;
    (*front)++;
    if (*front >= BUFFER_SIZE) {
        *front = 0;
    }
    return &data[place];
}