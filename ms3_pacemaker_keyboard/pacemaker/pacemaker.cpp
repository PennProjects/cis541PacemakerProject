/* pacemaker.cpp */ 

#include "pacemaker.h"
#include "mbed.h"


event Pacemaker::dispatch(unsigned int signal) {
CLK = t.read_ms(); // update clock variable 
switch (myState) {
    case READY: // IF we're in ready state, 
        switch (signal) {
            case PACE:
                if (eval_guard(rd_dis_pace)) { // if the timer approaches RI, reset timer and PACE heart 
                    t.stop(); 
                    t.reset(); 
                    t.start();  
                    RI = LRI; 
                    tran(DISABLED); 
                    return PACE; 
                }
                return SENSE; 
                break; 
            case SENSE: // if sense signal recieved, reset time and transition 
                t.stop(); 
                t.reset(); 
                t.start(); 
                RI = HRI; 
                tran(DISABLED); 
                return SENSE; 
                break; 
        }
        break; 
    case DISABLED: // If disabled, switch to READY if CLK >= VRP 
        if (eval_guard(dis_rd)) {tran(READY);}
    break; 
} return NONE; 
}

// evaluate guards
bool Pacemaker::eval_guard(int trn) { 
    switch(trn) {
        case rd_dis_pace:
            return CLK >= RI; 
        case dis_rd:
            return CLK >= VRP;
    }
    return false; 
}

void Pacemaker::init() {t.start(); CLK = 0; myState = READY; RI = LRI;}