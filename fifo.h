/*
fifo.h
Mohamed Magdi
10 JUL 2023
*/

#ifndef _FIFO_H_
#define _FIFO_H_

#define width 50

typedef struct
{
    unsigned int rollNum;
    char *fname;
    char *lname;
    float gpa;
    int courses[5];
} std_t;

typedef struct
{
    int length;
    int count;
    std_t *base;
    std_t *head;
    std_t *tail;
} fifo_t;

typedef enum
{
    FIFO_NO_ERROR,
    FIFO_FULL,
    FIFO_EMPTY,
    FIFO_NULL
} fifo_status_t;

// APIs

fifo_status_t fifoInit(fifo_t *fifo_buf, std_t buf[], int length);
fifo_status_t fifoEnqueue(fifo_t *fifo_buf, std_t item);
fifo_status_t fifoDequeque(fifo_t *fifo_buf, std_t *item);
fifo_status_t fifoIsFull(fifo_t *fifo_buf);
void printStudents(fifo_t *fifo_buf);

#endif
