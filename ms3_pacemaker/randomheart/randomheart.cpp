/* randomheart.cpp */ 
#include "randomheart.h"
#include "pacemaker.h"
#include "mbed.h"

// dispatch events for transitions 
event RandomHeart::dispatch(event signal) {
sinceBeat = t.read_ms();
switch (myState) {
    case NORMAL: // IF we're in ready state, 
        switch (signal) {
            case PACE:    // if we receive a PACE signal, beat the heart, tranistion state, and reset timer 
                targ = minInt + rand() % (int)(maxInt - minInt); // new random target time 
                t.stop(); 
                t.reset();
                t.start(); 
                tran(REF); 
                return PACE; 

            default: // if timer reaches random target, send SENSE signal, reset timer, and transition staet
                if(eval_guard(since_beat_min)) {
                    targ = minInt + rand() % (int)(maxInt - minInt); 
                    t.stop(); 
                    t.reset(); 
                    t.start(); 
                    tran(REF); 
                    return SENSE; 
                } else {
                    return PACE; 
                }
        }
        break; 
    case REF: // if we are in refractor state, tranistion to normal 
        tran(NORMAL); 
        return PACE; 
    break; 
}return NONE;
}

// evaluate guards 
bool RandomHeart::eval_guard(int trn) {
    switch(trn) {
        case since_beat_min: 
            return sinceBeat >= targ; 
    }
    return false; 
}