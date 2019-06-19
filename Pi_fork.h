//-----------------------------------------
// NAME		: Tianhao Wu
// STUDENT NUMBER	: 7794580
// COURSE		: COMP 3430
// INSTRUCTOR	: Franklin Bristow
// ASSIGNMENT	: assignment 1
// QUESTION	: question calculate Pi
//
// REMARKS: Head file for calculate Pi using fork.
//
//
//-----------------------------------------
// Created by larmititoth-OS on 2019-05-29.
//

#include <gmp.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#ifndef ASSIGNMENT_1_PI_FORK_H
#define ASSIGNMENT_1_PI_FORK_H

void calculatePi(int k,int digit);

#endif //ASSIGNMENT_1_PI_FORK_H
