//-----------------------------------------
// NAME		: Tianhao Wu
// STUDENT NUMBER	: 7794580
// COURSE		: COMP 3430
// INSTRUCTOR	: Franklin Bristow
// ASSIGNMENT	: assignment
// QUESTION	: question
//
// REMARKS: What is the purpose of this program?
//
//
//-----------------------------------------
// Created by larmititoth-OS on 2019-06-25.
//

#ifndef ASSIGNMENT_3_SIMULATION_HPP
#define ASSIGNMENT_3_SIMULATION_HPP

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <fstream>
#include <sstream>
#include <sys/timeb.h>
#include "Process.hpp"


//#define TIMESLICE 5
using namespace std;


class simulation {
private:
    int priorityTime[4];
    int priorityNum[4];
    int typeTime[5];
    int typeNum[5];
    process *pros;
    int globalTime;
    fstream inFile;
    static const int MAX=100;
    char reader[MAX];
    void countType();
    void timeAnalysis(processesNode *node,string type);
    void pureRR(string scheduling);
    void shortestTime(string scheduling);
    void multiRR(string scheduling);
    void printAnalysis( string type);
    long setRandomNum(int mod);
    processInfo* setupInfo();
public:
    simulation();
    void processSim(string file,string schedulingNum);
};


#endif //ASSIGNMENT_3_SIMULATION_HPP
