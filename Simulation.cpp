//-----------------------------------------
// NAME		: Tianhao Wu 
// STUDENT NUMBER	: 7794580
// COURSE		: COMP 3430
// INSTRUCTOR	: Franklin Bristow
// ASSIGNMENT	: assignment 3
// QUESTION	: question 1
// 
// REMARKS: What is the purpose of this program?
//
//
//-----------------------------------------
// Created by larmititoth-OS on 2019-06-25.
//

#include "Simulation.hpp"

const int TIMESLICE=5;

simulation::simulation() {
   globalTime=0;
   pros=new process();

}

void simulation::processSim(const string file,string schedulingNum) {

    string data;
    inFile.open(file);
    inFile.getline(reader,MAX);
    if(schedulingNum == "1"){
        pureRR(schedulingNum);
    } else if(schedulingNum == "2"){
        shortestTime(schedulingNum);
    } else if(schedulingNum == "3"){
        multiRR(schedulingNum);
    }

    inFile.close();
}


void simulation::pureRR(string scheduling) {
    while(!inFile.eof() && inFile.good()) {
        processInfo *newInfo = setupInfo();
        pros->insert(newInfo);
        inFile.getline(reader, MAX);
    }
    countType();
    processesNode *curr=pros->dequeue();
    while(curr!=NULL) {
        timeAnalysis(curr,scheduling);
        curr=pros->dequeue();
    }
    printAnalysis(scheduling);

}//pure Round-Robin


void simulation::shortestTime(string scheduling) {

    while(!inFile.eof() && inFile.good()) {
        processInfo *newInfo = setupInfo();
        pros->timeinsert(newInfo);
        inFile.getline(reader, MAX);
    }
    countType();
    while(!pros->isEmpty()) {

        processesNode *curr=pros->dequeue();
        if (curr != NULL) {
            timeAnalysis(curr,scheduling);
        }
    }
    printAnalysis(scheduling);

}//shortestTime first


void simulation::multiRR(string scheduling) {
    while(!inFile.eof() && inFile.good()){
        processInfo *newInfo=setupInfo();
        pros->priorityinsert(newInfo);
        inFile.getline(reader,MAX);
    }
    countType();
    while(!pros->isEmpty()) {
        processesNode *curr=pros->dequeue();
        if (curr != NULL) {
            timeAnalysis(curr,scheduling);
        }
    }
    printAnalysis(scheduling);

}//Multi-level Round-Robin


processInfo* simulation::setupInfo() {
    stringstream line(reader);
    processInfo* info=new processInfo();
    int *data=new int[5];
    if(!line.eof() && line.good()){
        line>>info->name;
        for (int i = 0; i < 4; ++i) {
            line>>data[i];
        }
    }
    info->type=data[0];
    info->priority=data[1];
    info->amount_of_time=data[2];
    info->odds=data[3];
    //delete[] data;
    return info;
}


void simulation::timeAnalysis(processesNode *node,const string type) {


    if (type == "1") {

        int ioTime=0;
        int random =setRandomNum(100);

        if (random > node->info->odds)
            ioTime = setRandomNum(5);


        if ((ioTime + node->info->amount_of_time) > TIMESLICE) {//remaining time is larger than time slice
            if(ioTime==0){
                node->info->amount_of_time -= TIMESLICE; //minus the ioTime in the amount as the normal RR.
                pros->insert(node->info);//re-requeue
                globalTime += TIMESLICE;
            } else {
                node->info->amount_of_time -= ioTime; //minus the ioTime in the amount as the normal RR.
                pros->insert(node->info);//re-requeue
                globalTime += ioTime;
            }

        } else if (( node->info->amount_of_time) < TIMESLICE) {//remaining time is smaller than time slice.
            node->info->amount_of_time -= ioTime + node->info->amount_of_time;
            globalTime += (node->info->amount_of_time + ioTime);
            if (node->info->priority == 0) {
                priorityTime[0] += globalTime;
            } else if (node->info->priority == 1) {
                priorityTime[1] += globalTime;
            } else if (node->info->priority == 2) {
                priorityTime[2] += globalTime;
            }

            if (node->info->type == 0) {
                typeTime[0] += globalTime;
            } else if (node->info->type == 1) {
                typeTime[1] += globalTime;
            } else if (node->info->type == 2) {
                typeTime[2] += globalTime;
            } else if (node->info->type == 3) {
                typeTime[3] += globalTime;
            }
        }


    } else if (type == "2") {
//        int ioTime;
//        int random = (rand() % 101) + 0;
//
//        if (random > node->info->odds) {
//            ioTime = (rand() % 5) + 1;
//            globalTime += ioTime;
//        }//since STF using different policy therefore it doesn't need ioTime.

        if (node->info->priority == 0) {
            priorityTime[0] += node->info->amount_of_time + globalTime;

        } else if (node->info->priority == 1) {
            priorityTime[1] += node->info->amount_of_time + globalTime;

        } else if (node->info->priority == 2) {
            priorityTime[2] += node->info->amount_of_time + globalTime;

        }
        if (node->info->type == 0) {
            typeTime[0] += node->info->amount_of_time + globalTime;

        } else if (node->info->type == 1) {
            typeTime[1] += node->info->amount_of_time + globalTime;

        } else if (node->info->type == 2) {
            typeTime[2] += node->info->amount_of_time + globalTime;

        } else if (node->info->type == 3) {
            typeTime[3] += node->info->amount_of_time + globalTime;

        }
        globalTime += node->info->amount_of_time;


    } else if (type == "3") {
        int ioTime=0;
        int random =setRandomNum(100);

        if (random > node->info->odds)
            ioTime = setRandomNum(5);


        if (node->info->amount_of_time > TIMESLICE) {//remaining time is larger than time slice
            if(ioTime==0){
                node->info->amount_of_time -= TIMESLICE; //minus the ioTime in the amount as the normal RR.
                pros->priorityinsert(node->info);//re-requeue
                globalTime += TIMESLICE;
            } else {
                node->info->amount_of_time -= ioTime; //minus the ioTime in the amount as the normal RR.
                pros->priorityinsert(node->info);//re-requeue
                globalTime += ioTime;
            }

        } else if (node->info->amount_of_time < TIMESLICE) {//remaining time is smaller than time slice.
            node->info->amount_of_time -= node->info->amount_of_time;
            globalTime += node->info->amount_of_time;
            if (node->info->priority == 0) {
                priorityTime[0] += globalTime;
            } else if (node->info->priority == 1) {
                priorityTime[1] += globalTime;
            } else if (node->info->priority == 2) {
                priorityTime[2] += globalTime;
            }

            if (node->info->type == 0) {
                typeTime[0] += globalTime;
            } else if (node->info->type == 1) {
                typeTime[1] += globalTime;
            } else if (node->info->type == 2) {
                typeTime[2] += globalTime;
            } else if (node->info->type == 3) {
                typeTime[3] += globalTime;
            }
        }


    }

}
    void simulation::printAnalysis(string scheduling) {

        if (scheduling == "1")
            cout << "Using pure round-robin\n" << endl;
        else if (scheduling == "2")
            cout << "Using Shortest time to completion first\n" << endl;
        else if (scheduling == "3")
            cout << "Using Priority round-robin.\n" << endl;
        int P_0_time = priorityTime[0] / priorityNum[0];
        int P_1_time = priorityTime[1] / priorityNum[1];
        int P_2_time = priorityTime[2] / priorityNum[2];
        cout << "Average run time per priority:\n" <<
             "Priority 0 average run time:" << P_0_time << "\n" <<
             "Priority 1 average run time:" << P_1_time << "\n" <<
             "Priority 2 average run time:" << P_2_time << "\n" << endl;

        P_0_time = typeTime[0] / typeNum[0];
        P_1_time = typeTime[1] / typeNum[1];
        P_2_time = typeTime[2] / typeNum[2];
        int P_3_time = typeTime[3] / typeNum[3];

        cout << "Average run time per type: \n" <<
             "Type 0 average run time:" << P_0_time << "\n" <<
             "Type 1 average run time:" << P_1_time << "\n" <<
             "Type 2 average run time:" << P_2_time << "\n" <<
             "Type 3 average run time:" << P_3_time << "\n" << endl;

    }


void simulation::countType() {
    processesNode *node=pros->start;

    for (int i = 0; i <4 ; ++i) {
        priorityTime[i]=0;
        typeTime[i]=0;
    }
    for (int i = 0; i <5 ; ++i) {
        priorityNum[i]=0;
        typeNum[i]=0;
    }
    while(node!=NULL) {

        if (node->info->priority == 0) {
           priorityNum[0]+=1;
        } else if (node->info->priority == 1) {
            priorityNum[1]+=1;
        } else if (node->info->priority == 2) {
            priorityNum[2]+=1;
        }
        if (node->info->type == 0) {
            typeNum[0]+=1;
        } else if (node->info->type == 1) {
            typeNum[1]+=1;
        } else if (node->info->type == 2) {
            typeNum[2]+=1;
        } else if (node->info->type == 3) {
            typeNum[3]+=1;
        }
        node=node->next;
    }


}

long simulation::setRandomNum(int mod) {

    timeb t;
    ftime(&t);
    return (t.time * 1000 + t.millitm)% mod+1;
}


