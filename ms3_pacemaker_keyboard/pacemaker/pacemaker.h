#ifndef PACEMAKER_H
#define PACEMAKER_H

#include "mbed.h"

const int LRL = 55;      //bpm of lover rate limit 
const int HRL = 40;      //bpm of of the slowest the heart should ever beat 
const int LRI = 1090;    // ms: LRL 55 bpm 
const int HRI = 1500;    // ms: HRL 40 bpm 
const int VRP = 320;     // ms: refractory period to prevebt corrsstalk


enum State {READY, DISABLED};               // FSM states of Pacemaker 
enum event {PACE, SENSE};                   // events for transitioning states 
enum Transition {rd_dis_pace, rd_dis_sense, dis_rd}; // pacemaker transitions 


// Pacemaker Class
class Pacemaker {
private:
    Timer t; // internal timer 
    int RI;  // keeps track of rate interval for max time before pacing 
    bool eval_guard(int trn); 

public: 
    State myState; // current state
    double CLK; // internal clock  
    void init();
    event dispatch(unsigned int sig); // dispatch events 
    void tran(State target) {myState = target;}  // transitions 
};

#endif