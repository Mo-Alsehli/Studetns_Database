#include <stdio.h>
#include <stdlib.h>
#include "studentsFifo.h"
#include "fifo.h"

fifo_t studentsBuf;
std_t studentsDatabase[width];

int main()
{
    int option;

    if (fifoInit(&studentsBuf, studentsDatabase, width) == FIFO_NO_ERROR)
    {
        printf("\n[INFO] Fifo Initialization Success... :)\n");
    }
    else if (fifoInit(&studentsBuf, studentsDatabase, width) == FIFO_NULL)
    {
        printf("\n[ERROR] Fifo Initialization Faild... :(\n");
    }

    while (1)
    {
        printf("\n<< =============== STUDENTS DATABASE =================== >>\n\n");
        printf("1. Add Students Data From A File\n");
        printf("2. Add Students Manually\n");
        printf("3. Print Students\n");
        printf("4. Find Student By Roll Number\n");
        printf("5. Find Student By First Name\n");
        printf("6. Find Students Enrolled In A Course\n");
        printf("7. Get The Total Number Of Students\n");
        printf("8. Delete Student With Roll Number\n");
        printf("9. Update Student Data\n");
        printf("\nEnter Option Number Or -1 To Exit: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            addStudentsDataFromFile(&studentsBuf, "students.txt");
            break;
        case 2:
            addStudentManually(&studentsBuf);
            break;
        case 3:
            printStudents(&studentsBuf);
            break;
        case 4:
            findStdByRollNum(&studentsBuf);
            break;
        case 5:
            findStdByFname(&studentsBuf);
            break;
        case 6:
            findStdsRegisterdInACourse(&studentsBuf);
            break;
        case 7:
            stdCount(&studentsBuf);
            break;
        case 8:
            deleteStd(&studentsBuf);
            break;
        case 9:
            updateStd(&studentsBuf);
            break;
        default:
            exit(0);
            break;
        }
    }

    return 0;
}