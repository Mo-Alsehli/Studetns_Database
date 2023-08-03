/**
 *****************************************************************************
 * @project        : Students Database
 * @file           : studentsFifo.h
 * @author         : Mohamed Magdi
 * @Created on     : 1 AUG, 2023
 ******************************************************************************
 */

#ifndef STUDENTSFIFO_H_
#define STUDENTSFIFO_H_

#include "fifo.h"

// Funciton Declarations:
fifo_status_t addStudentsDataFromFile(fifo_t *fifoBuf, char *fileName);
fifo_status_t addStudentManually(fifo_t *fifoBuf);
fifo_status_t findStdByRollNum(fifo_t *fifoBuf);
fifo_status_t findStdByFname(fifo_t *fifoBuf);
fifo_status_t findStdsRegisterdInACourse(fifo_t *fifoBuf);
fifo_status_t stdCount(fifo_t *fifoBuf);
fifo_status_t deleteStd(fifo_t *fifoBuf);
fifo_status_t updateStd(fifo_t *fifoBuf);
fifo_status_t findStdByRollNumHelper(fifo_t *fifoBuf, unsigned int rollNum);

#endif