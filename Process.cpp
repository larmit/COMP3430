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

#include "Process.hpp"

processInfo::processInfo():type(0),priority(0),amount_of_time(0),odds(0){}

processInfo::processInfo(string name, int type, int priority, int amount, int odds):type(type),
priority(priority),amount_of_time(amount),odds(odds),timecost(0){
    this->name=std::move(name);
   }

processesNode::processesNode():next(NULL){this->info=NULL;}
processesNode::processesNode(processInfo *info):info(info),next(NULL){}
processesNode::processesNode(processInfo *info, processesNode *next):info(info),next(next) {}


process::process() {
    start=end=NULL;
}
bool process::isEmpty() {
    return (start==NULL);
}

void processInfo::print(){
    cout<<name<<" type:"<<type<<" P:"<<priority <<" time:"<<amount_of_time<<" odds:"<<odds<<endl;
}
void process::insert(processInfo *process) {
    if(start==NULL){
       start=new processesNode(process);
       end=start;
    } else{
        end->next=new processesNode(process);
        end=end->next;
    }
}

void process::priorityinsert(processInfo *info) {
    processesNode *curr=start;
    processesNode *prev=curr;
    if(start== NULL){
        start=new processesNode(info);
        end=start;
    } else if(start->next == NULL){
        if(info->priority < start->info->priority){
            processesNode *newNode=new processesNode(info,start);
            start=newNode;
            end=start->next;
        } else{
            start->next=new processesNode(info);
            end=start->next;
        }

    } else{
        while(curr!=end && curr->info->priority <= info->priority){
            prev=curr;
            curr=curr->next;
        }
        if(curr==end){
            if(curr->info->priority > info->priority){
                prev->next=new processesNode(info,curr);
            } else{
                curr->next=new processesNode(info,NULL);
                end=curr->next;
            }
        } else if(curr== start){
            processesNode *newNode=new processesNode(info,start);
            start=newNode;
        } else{
            prev->next= new processesNode(info,curr);
        }
    }
}


void process::timeinsert(processInfo *info) {
    processesNode *curr=start;
    processesNode *prev=curr;
    if(start== NULL){
        start=new processesNode(info);
        end=start;
    } else if(start->next == NULL){
        if(info->amount_of_time < start->info->amount_of_time){
            processesNode *newNode=new processesNode(info,start);
            start=newNode;
            end=start->next;
        } else{
            start->next=new processesNode(info);
            end=start->next;
        }
    } else{
        while(curr!=end && curr->info->amount_of_time <= info->amount_of_time){
            prev=curr;
            curr=curr->next;
        }
        if(curr==end){
            if(curr->info->amount_of_time > info->amount_of_time){
                prev->next=new processesNode(info,curr);
            } else{
                curr->next=new processesNode(info,NULL);
                end=curr->next;
            }
        } else if(curr== start){
            processesNode *newNode=new processesNode(info,start);
            start=newNode;
        } else{
            prev->next= new processesNode(info,curr);
        }
    }
}

processesNode* process::dequeue() {
    processesNode* result=start;
    if(start!=NULL)
        start=start->next;
    else if(start==NULL)
        result=NULL;

    if(start==NULL)
        end=NULL;

    return result;
}
