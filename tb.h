#include <systemc.h>
#

SC_MODULE(tb) {
    sc_out< sc_int<16> > a;
    sc_out< sc_int<16> > b;

    void stimulus();
    void display();

    SC_CTOR(tb) {
        SC_THREAD(stimulus);
        SC_METHOD(display);
        sensitive << a << b;
    }

};

