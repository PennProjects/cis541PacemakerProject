#ifndef RANDOMHEART_H
#define RANDOMHEART_H

#include "mbed.h"
#include "pacemaker.h"      // NOTE: we need SENSE and PACE events from pacemaker.h 

const int minInt = 100; // ms : minimum beat 
const int maxInt = 1900; // ms : max time before another beat

enum State_h {NORMAL, REF};  // FSM states to model random heart
enum Transition_h {PACED, SELFBEAT, since_beat_min} ;  // tranistions between states 

/* RandomHeart class */ 
class RandomHeart {
private:
    double targ;                    // random target time for next self beat  
    Timer t;                        // internall timer 
    State_h myState;                // current state
    bool eval_guard(int trn); 

public: 
    double sinceBeat; // internal clock 
    void init() {t.start(), sinceBeat = 0; myState = NORMAL;
        targ = minInt + rand() % (int)(maxInt - minInt);} // init random target beat time 
    event dispatch(event signal); 
    void tran(State_h target) {myState = target;}
};

#endif 
