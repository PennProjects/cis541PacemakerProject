/* randomheart.cpp */ 
#include "randomheart.h"
#include "pacemaker.h"
#include "mbed.h"
#include <chrono>

event RandomHeart::dispatch(event signal) {
sinceBeat = t.read_ms();
switch (myState) {
    case NORMAL: // IF we're in ready state, 
        switch (signal) {
            case PACE:
                //sinceBeat = 0; 
                targ = minInt + rand() % (int)(maxInt - minInt); 
                t.stop(); 
                t.reset();
                t.start(); 
                tran(REF); 
                return PACE; 

            default:
                if(eval_guard(since_beat_min)) {
                    //sinceBeat = 0; 
                    targ = minInt + rand() % (int)(maxInt - minInt); 
                    t.stop(); 
                    t.reset(); 
                    t.start(); 
                    tran(REF); 
                    // TODO: send SENSE
                    return SENSE; 
                } else {
                    return PACE; 
                }
        }
        break; 
    case REF: 
        tran(NORMAL); 
        return PACE; 
    break; 
}return NONE;
}


bool RandomHeart::eval_guard(int trn) {
    switch(trn) {
        case since_beat_min: 
            return sinceBeat >= targ; 
    }
    return false; 
}