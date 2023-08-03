/**
 *****************************************************************************
 * @project        : Students Database
 * @file           : studentsFifo.c
 * @author         : Mohamed Magdi
 * @Created on     : 1 AUG, 2023
 ******************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "studentsFifo.h"
#include "fifo.h"

#define MAX_STRING_LENGTH 100

// Read Data From A File.
fifo_status_t addStudentsDataFromFile(fifo_t *fifoBuf, char *fileName)
{
    if (!fileName)
    {
        printf("\n[Error] File Name....\n");
        return FIFO_NULL;
    }
    else if (fifoBuf == NULL)
    {
        printf("\n[Error] Fifo Buffer....\n");
        return FIFO_NULL;
    }
    FILE *filePtr;
    filePtr = fopen(fileName, "r");
    std_t newStudent;
    int numStudents = 0;
    char line[MAX_STRING_LENGTH];

    while (numStudents < 50 && fgets(line, sizeof(line), filePtr) != NULL)
    {
        unsigned int rollNum;
        char fname[MAX_STRING_LENGTH];
        char lname[MAX_STRING_LENGTH];
        float gpa;
        int courses[5];

        sscanf(line, "%u %s %s %f %d %d %d %d %d", &rollNum, fname, lname, &gpa, &courses[0], &courses[1], &courses[2], &courses[3], &courses[4], &courses[5]);
        if (findStdByRollNumHelper(fifoBuf, rollNum) == FIFO_NULL)
        {
            newStudent.rollNum = rollNum;
            newStudent.fname = strdup(fname);
            newStudent.lname = strdup(lname);
            newStudent.gpa = gpa;
            for (int i = 0; i < 5; i++)
            {
                newStudent.courses[i] = courses[i];
            }

            if (fifoEnqueue(fifoBuf, newStudent) == FIFO_NO_ERROR)
            {
                printf("[INFO] Roll Number: %d Added Successfully... \n", rollNum);
            }
            else
            {
                printf("[Error] Faild To Add Roll Number: %d\n", rollNum);
            }

            numStudents++;
        }
        else if (findStdByRollNumHelper(fifoBuf, rollNum) == FIFO_NO_ERROR)
        {
            printf("\n[ERROR] The Roll Number Must Be Unique, Roll Number (%d) Already Exists !!! \n\n", rollNum);
        }
    }

    fclose(filePtr);
    return FIFO_NO_ERROR;
}

// Add Student Manually Function:
fifo_status_t addStudentManually(fifo_t *fifoBuf)
{
    std_t student;
    char fname[MAX_STRING_LENGTH];
    char lname[MAX_STRING_LENGTH];
    printf("Enter Student Details: \n");
    printf("Enter Student Unique Roll Number: ");
    scanf("%d", &(student.rollNum));
    if (findStdByRollNumHelper(fifoBuf, student.rollNum) == FIFO_NULL)
    {

        printf("Enter Student First Name: ");
        scanf("%s", fname);
        printf("Enter Student Last Name: ");
        scanf("%s", lname);
        printf("Enter Student GPA: ");
        scanf("%f", &(student.gpa));
        printf("Enter Student Registered Courses IDs: \n");
        for (int i = 0; i < 5; i++)
        {
            printf("Course(%d) ID: ", i + 1);
            scanf("%d", &(student.courses[i]));
        }

        student.fname = strdup(fname);
        student.lname = strdup(lname);

        if (fifoEnqueue(fifoBuf, student) == FIFO_NO_ERROR)
        {
            printf("[INFO] Roll Number: %d Added Successfully... \n", student.rollNum);
        }
        else
        {
            printf("[Error] Faild To Add Roll Number: %d\n", student.rollNum);
        }
    }
    else if (findStdByRollNumHelper(fifoBuf, student.rollNum) == FIFO_NO_ERROR)
    {
        printf("\n[ERROR] The Roll Number Must Be Unique, Roll Number (%d) Already Exists !!! \n\n", student.rollNum);
    }
    return FIFO_NO_ERROR;
}

// Find Student By His Roll Number.
fifo_status_t findStdByRollNum(fifo_t *fifoBuf)
{
    unsigned int rollNum;
    std_t *temp;
    temp = fifoBuf->tail;
    int i, length = fifoBuf->count;

    printf("Enter The Student Unique Roll Number: ");
    scanf("%u", &rollNum);

    for (i = 0; i < length; i++)
    {
        if (temp->rollNum == rollNum)
        {
            printf("\n-----------------------------------------------");
            printf("\n[INFO] Found Student With Roll Number (%d)...\n", rollNum);
            printf("-----------------------------------------------\n");
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
            return FIFO_NO_ERROR;
        }
        temp++;
    }

    printf("\n[ERROR] Student With Roll Number (%d) Not Found... :(\n", rollNum);
    return FIFO_NULL;
}

// Find Student By His Name
fifo_status_t findStdByFname(fifo_t *fifoBuf)
{
    char fname[MAX_STRING_LENGTH];
    std_t *temp;
    temp = fifoBuf->tail;
    int i, length = fifoBuf->count;

    printf("Enter The Student First Name: ");
    scanf("%s", fname);

    for (i = 0; i < length; i++)
    {
        if (strcmp(temp->fname, fname) == 0)
        {

            printf("\n-----------------------------------------------");
            printf("\n[INFO] Found Student With First Name (%s)...\n", fname);
            printf("-----------------------------------------------\n");
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
            return FIFO_NO_ERROR;
        }
        temp++;
    }

    printf("\n[ERROR] Student With First Name (%s) Not Found... :(\n", fname);
    return FIFO_NULL;
}

// Find The Students Registered In A Specific Course.
fifo_status_t findStdsRegisterdInACourse(fifo_t *fifoBuf)
{
    std_t *temp;
    fifo_t tempBuf;
    std_t studentsDatabase[width];

    fifoInit(&tempBuf, studentsDatabase, width);

    int courseId, i, j, length = fifoBuf->count;
    temp = fifoBuf->tail;

    printf("\nEnter The Course ID: ");
    scanf("%d", &courseId);

    for (i = 0; i < length; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (temp->courses[j] == courseId)
            {
                fifoEnqueue(&tempBuf, *temp);
            }
        }
        temp++;
    }

    printf("\n[INFO] The Students Enrolled In The Course (%d)....\n", courseId);
    printStudents(&tempBuf);

    return FIFO_NO_ERROR;
}

// Get The Total Number Of Students.
fifo_status_t stdCount(fifo_t *fifoBuf)
{

    printf("\n[INFO] The Total Number Of Students Is: %d\n", fifoBuf->count);
    printf("[INFO] You Can Add A Total %d Students\n", fifoBuf->length);
    printf("[INFO] You Can Add %d More Students\n\n", fifoBuf->length - fifoBuf->count);

    return FIFO_NO_ERROR;
}

// Delete A Student With A Roll Number.
fifo_status_t deleteStd(fifo_t *fifoBuf)
{
    unsigned int rollNum;
    std_t *curr, *next;
    curr = fifoBuf->tail;
    next = fifoBuf->tail;
    next++;
    int i, length = fifoBuf->count;

    printf("\nEnter The Student Unique Roll Number: ");
    scanf("%u", &rollNum);

    for (i = 0; i < length; i++)
    {
        if (curr->rollNum == rollNum)
        {
            while (next != fifoBuf->head)
            {
                *curr = *next;
                curr++;
                next++;
            }
            printf("\n[INFO] Student With Roll Number (%d) Deleted :)\n\n", rollNum);
            fifoBuf->head--;
            fifoBuf->count--;

            return FIFO_NO_ERROR;
        }
        curr++;
        next++;
    }

    printf("\n[ERROR] There Is No Student With Roll Number (%d) :(\n\n", rollNum);

    return FIFO_NULL;
}

// Update The Data Of A Student.
fifo_status_t updateStd(fifo_t *fifoBuf)
{
    unsigned int rollNum;
    std_t *temp;
    temp = fifoBuf->tail;
    int i, length = fifoBuf->count;
    char fname[MAX_STRING_LENGTH];
    char lname[MAX_STRING_LENGTH];
    printf("\nEnter Roll Number For Student To Update: ");
    scanf("%u", &rollNum);

    for (i = 0; i < length; i++)
    {
        if (temp->rollNum == rollNum)
        {
            printf("\n1. Roll Number\n");
            printf("2. First Name\n");
            printf("3. Last Name\n");
            printf("4. GPA\n");
            printf("5. Courses\n");

            printf("\nChoose Entry To Be Updated: ");
            scanf("%d", &i);

            switch (i)
            {
            case 1:
                printf("\nEnter The New Roll Number: ");
                scanf("%u", &(temp->rollNum));
                break;
            case 2:

                printf("\nEnter The New First Name: ");
                scanf("%s", fname);
                temp->fname = strdup(fname);
                break;
            case 3:

                printf("\nEnter The New Last Name: ");
                scanf("%s", lname);
                temp->lname = strdup(lname);
                break;
            case 4:
                printf("\nEnter The New GPA: ");
                scanf("%f", &(temp->gpa));
                break;
            case 5:
                printf("\nEnter The New Courses: ");
                printf("Enter Student Registered Courses IDs: \n");
                for (i = 0; i < 5; i++)
                {
                    printf("Course(%d) ID: ", i + 1);
                    scanf("%d", &(temp->courses[i]));
                }
                break;
            default:
                printf("\nWrong Option...");
                break;
            }
            printf("\n[INFO] Student With Roll Number (%d), Updated Successfully\n", rollNum);
            return FIFO_NO_ERROR;
        }
    }

    printf("\n[ERROR] There is no student with roll Number (%d)....\n", rollNum);

    return FIFO_NULL;
}

// A Helper Function.
fifo_status_t findStdByRollNumHelper(fifo_t *fifoBuf, unsigned int rollNum)
{
    std_t *temp;
    temp = fifoBuf->tail;
    int i, length = fifoBuf->count;

    for (i = 0; i < length; i++)
    {
        if (temp->rollNum == rollNum)
        {
            return FIFO_NO_ERROR;
        }
        temp++;
    }

    return FIFO_NULL;
}
