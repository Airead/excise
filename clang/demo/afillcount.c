#include <stdio.h>
#include <malloc.h>
 
/* This approach replaces the CircularBuffer 'end' field with the
   'count' field and changes these functions: */

/* Opaque buffer element type.  This would be defined by the application. */
typedef struct { int value; } ElemType;
 
/* Circular buffer object */
typedef struct {
    int         size;   /* maximum number of elements           */
    int         start;  /* index of oldest element              */
    int         count;    /* index at which to write new element  */
    ElemType   *elems;  /* vector of elements                   */
} CircularBuffer;
 
void cbInit(CircularBuffer *cb, int size) {
    cb->size  = size;
    cb->start = 0;
    cb->count = 0;
    cb->elems = (ElemType *)calloc(cb->size, sizeof(ElemType));
}
 
int cbIsFull(CircularBuffer *cb) {
    return cb->count == cb->size; }
 
int cbIsEmpty(CircularBuffer *cb) {
    return cb->count == 0; }
 
void cbWrite(CircularBuffer *cb, ElemType *elem) {
    int end = (cb->start + cb->count) % cb->size;
    cb->elems[end] = *elem;
    if (cb->count == cb->size)
        cb->start = (cb->start + 1) % cb->size; /* full, overwrite */
    else
        ++ cb->count;
}
 
void cbRead(CircularBuffer *cb, ElemType *elem) {
    *elem = cb->elems[cb->start];
    cb->start = (cb->start + 1) % cb->size;
    -- cb->count;
}

void cbFree(CircularBuffer *cb) {
    free(cb->elems); /* OK if null */ }

int main(int argc, char **argv) {
    CircularBuffer cb;
    ElemType elem = {0};
 
    int testBufferSize = 10; /* arbitrary size */
    cbInit(&cb, testBufferSize);
 
    /* Fill buffer with test elements 3 times */
    for (elem.value = 0; elem.value < 3 * testBufferSize; ++ elem.value)
        cbWrite(&cb, &elem);
 
    /* Remove and print all elements */
    while (!cbIsEmpty(&cb)) {
        cbRead(&cb, &elem);
        printf("%d\n", elem.value);
    }
 
    cbFree(&cb);
    return 0;
}
