//
// Created by aluck on 21.06.20.
//

#include <systemc.h>
#include "FullAdder.h"

void FullAdder::add() {
    sc_int<16> tmp_a;
    sc_int<16> tmp_b;
    sc_int<17> tmp_r;

    tmp_a = (sc_int<16>)a.read();
    tmp_b = (sc_int<16>)b.read();

    while (true) {
        tmp_r = tmp_a + tmp_b;
        wait(2, SC_NS);
        result.write(tmp_r);
        wait();
    }
}
void FullAdder::display() {
    cout<<"||sum  @ "<<sc_time_stamp()<<"\t:\t\t\t"<<result<<endl;
   }


