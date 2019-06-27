#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <fstream>
#include <sstream>
#include "Simulation.hpp"

using namespace std;


int main(int argc, char** argv) {
    if(argc<3){
        fprintf(stderr,"Need three argument, file name and the scheduling algorithm you wanna run.\n");
        exit(EXIT_FAILURE);
    }
    simulation *sim=new simulation();
    sim->processSim(argv[1],argv[2]);

    exit(EXIT_SUCCESS);
}
