//
// Created by aluck on 21.06.20.
//
#include <systemc.h>

SC_MODULE(FullAdder) {
    sc_in<sc_int<16>> a;
    sc_in<sc_int<16>> b;
    sc_out<sc_int<17>> result;

    void add();
    void display();

    SC_CTOR(FullAdder) {
        SC_METHOD(add);
        sensitive << a << b;
        dont_initialize();

        SC_THREAD(display);
        sensitive << result;
        dont_initialize();
    }

};


