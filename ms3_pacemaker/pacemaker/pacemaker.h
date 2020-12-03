#ifndef PACEMAKER_H
#define PACEMAKER_H

#include "mbed.h"
#include <chrono>

const int LRL = 55;      //bpm of lover rate limit 
const int HRL = 40;      //bpm of of the slowest the heart should ever beat 
const int LRI = 1090;    // ms: LRL 55 bpm 
const int HRI = 1500;    // ms: HRL 40 bpm 
const int VRP = 320;     // ms: refractory period to prevebt corrsstalk


enum State {READY, DISABLED};
enum event {PACE, SENSE, VRP_MIN, NONE}; 
enum Transition {rd_dis_pace, rd_dis_sense, dis_rd}; 



class Pacemaker {
private:
    Timer t; 
    int RI;  
    bool eval_guard(int trn); 

public: 
    State myState; 
    double CLK; // internal clock  
    void init();
    event dispatch(unsigned int sig); 
    void tran(State target) {myState = target;}
};

#endif