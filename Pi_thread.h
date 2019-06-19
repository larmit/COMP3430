//-----------------------------------------
// NAME		: Tianhao Wu
// STUDENT NUMBER	: 7794580
// COURSE		: COMP 3430
// INSTRUCTOR	: Franklin Bristow
// ASSIGNMENT	: assignment 1
// QUESTION	: question calculate Pi
//
// REMARKS: Head file for calculate Pi using thread.
//
//
//-----------------------------------------
// Created by larmititoth-OS on 2019-05-29.
//

#include <gmp.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#ifndef ASSIGNMENT_1_PI_THREAD_H
#define ASSIGNMENT_1_PI_THREAD_H
void* subCalculate(void* currentK);
void threadPi(int k,int digit);

#endif //ASSIGNMENT_1_PI_THREAD_H
