//-----------------------------------------
// NAME		: Tianhao Wu
// STUDENT NUMBER	: 7794580
// COURSE		: COMP 3430
// INSTRUCTOR	: Franklin Bristow
// ASSIGNMENT	: assignment 1
// QUESTION	: question calculate Pi
//
// REMARKS: call functions and count time.
//
//
//-----------------------------------------
// Created by larmititoth-OS on 2019-05-29.
//


#include "Pi_fork.h"
#include "Pi_thread.h"
#include <time.h>
#define PRECISION 300
#define DIGIT  200


struct timespec diff(struct timespec start, struct timespec end);
void timeCountThread();
void timeCountProcess();



int main() {

    timeCountThread();
    timeCountProcess();


    return 0;
}




void timeCountThread(){
    long timePeriod;
    struct timespec time1,time2;
    //counting time for threads.
    clock_gettime(CLOCK_THREAD_CPUTIME_ID,&time1);
    threadPi(PRECISION,DIGIT);
    clock_gettime(CLOCK_THREAD_CPUTIME_ID,&time2);

    timePeriod=diff(time1,time2).tv_nsec;
    printf("\n\n The time required for calculating %d digits Pi with precision %d by thread"
           " is %ld nanoseconds.\n\n",DIGIT,PRECISION,timePeriod);

}

void timeCountProcess(){
    long timePeriod;
    struct timespec time1,time2;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time1);
    calculatePi(PRECISION,DIGIT);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time2);

    timePeriod=diff(time1,time2).tv_nsec;
    printf("\n\n The time required for calculating %d digits Pi with precision %d by fork"
           " is %ld nanoseconds.\n",DIGIT,PRECISION,timePeriod);

}

struct timespec diff(struct timespec start, struct timespec end)
{
    struct timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}


