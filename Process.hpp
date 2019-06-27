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
// Created by larmititoth-OS on 2019-06-24.
//

#ifndef ASSIGNMENT_3_PROCESS_HPP
#define ASSIGNMENT_3_PROCESS_HPP
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;


class processInfo{
public:
    string name;
    int type;
    int priority;
    int amount_of_time;
    int odds;
    int timecost;
    processInfo();
    void print();
    processInfo(string name,int type,int priority,int amount,int odds);
};

class processesNode {
public:
    processInfo *info;
    processesNode *next;

    processesNode();
    processesNode(processInfo *info);
    processesNode(processInfo *info, processesNode *next);
};

class process {
public:
processesNode *start;
processesNode *end;
process();

bool isEmpty();
void insert(processInfo *info);
void priorityinsert(processInfo *info);
void timeinsert(processInfo *info);
processesNode* dequeue();

};


#endif //ASSIGNMENT_3_PROCESS_HPP
