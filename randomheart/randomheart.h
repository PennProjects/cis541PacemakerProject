#ifndef RANDOMHEART_H
#define RANDOMHEART_H

#include "mbed.h"
#include <chrono>
#include "pacemaker.h"

const int minInt = 100; // ms : minimum beat 
const int maxInt = 1900; // ms : max time before another beat

enum State_h {NORMAL, REF};
enum Transition_h {PACED, SELFBEAT, since_beat_min} ; 

/* RandomHeart class */ 
class RandomHeart {
private:
    double targ; 
    Timer t; 
    State_h myState; 
    bool eval_guard(int trn); 

public: 
    double sinceBeat; // internal clock 
    void init() {t.start(), sinceBeat = 0; myState = NORMAL;
        targ = minInt + rand() % (int)(maxInt - minInt);}
    event dispatch(event signal); 
    void tran(State_h target) {myState = target;}
};

#endif 
