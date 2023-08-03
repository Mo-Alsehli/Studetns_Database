#include <fifo.h>
#include <stdio.h>

fifo_status_t fifoInit(fifo_t *fifo_buf, std_t *buf, int length)
{
    if (buf == NULL)
        return FIFO_NULL;

    fifo_buf->head = buf;
    fifo_buf->base = buf;
    fifo_buf->tail = buf;
    fifo_buf->length = length;
    fifo_buf->count = 0;

    return FIFO_NO_ERROR;
}

fifo_status_t fifoEnqueue(fifo_t *fifo_buf, std_t item)
{
    if (!fifo_buf->head || !fifo_buf->tail || !fifo_buf->base)
        return FIFO_NULL;

    if (fifoIsFull(fifo_buf) == FIFO_FULL)
    {
        return FIFO_FULL;
    }

    *(fifo_buf->head) = item;
    fifo_buf->count++;

    if (fifo_buf->head == fifo_buf->base + (fifo_buf->length * sizeof(std_t)))
    {
        fifo_buf->head = fifo_buf->base;
    }
    else
    {
        fifo_buf->head++;
    }

    return FIFO_NO_ERROR;
}

fifo_status_t fifoIsFull(fifo_t *fifo_buf)
{
    if (!fifo_buf->head || !fifo_buf->tail || !fifo_buf->base)
        return FIFO_NULL;

    if (fifo_buf->count == fifo_buf->length)
    {
        return FIFO_FULL;
    }

    return FIFO_NO_ERROR;
}

fifo_status_t fifoDequeque(fifo_t *fifo_buf, std_t *item)
{
    if (!fifo_buf->head || !fifo_buf->tail || !fifo_buf->base)
        return FIFO_NULL;

    if (fifo_buf->count == 0)
    {
        return FIFO_EMPTY;
    }

    *item = *(fifo_buf->tail);
    fifo_buf->count--;
    if (fifo_buf->tail == (fifo_buf->base + fifo_buf->length * sizeof(std_t)))
    {
        fifo_buf->tail = fifo_buf->base;
    }
    else
    {
        fifo_buf->tail++;
    }

    return FIFO_NO_ERROR;
}

void printStudents(fifo_t *fifo)
{
    std_t *temp = 0;
    int i;

    if (fifo->count == 0)
    {
        printf("Fifo Is Empty !!!!\n\n");
    }
    else
    {
        temp = fifo->tail;
        printf("\n============= Print FIFO =================\n");
        for (i = 0; i < fifo->count; i++)
        {
            printf("\nStudent Number (%d).....\n", i + 1);
            printf("\tStudent Roll Number: %d \n", temp->rollNum);
            printf("\tStudent First Name: %s \n", temp->fname);
            printf("\tStudent Last Name: %s \n", temp->lname);
            printf("\tStudent GPA: %.2f \n", temp->gpa);
            printf("\tStudent Registered Courses IDs: ");
            for (int j = 0; j < 5; j++)
            {
                printf("  %d", temp->courses[j]);
            }
            printf("\n");
            temp++;
        }
        printf("\n\t============= DONE =============\n");
    }
}