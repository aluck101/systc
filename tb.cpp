
#include "tb.h"
#include "FullAdder.h"

void tb::stimulus() {
    a.write(0);
    b.write(0);
    wait(5,SC_NS);

    a.write(6);
    b.write(0);
    wait(2,SC_NS);

    a.write(4);
    b.write(5);
    wait(8,SC_NS);

    a.write(7);
    b.write(9);
    wait(3,SC_NS);

    a.write(3);
    b.write(5);
    wait(5,SC_NS);

    a.write(13);
    b.write(22);
    wait(9,SC_NS);

    a.write(1);
    b.write(7);
    wait(5,SC_NS);

    sc_stop();
}

void tb::display() {
    cout<<"inputs @"<<sc_time_stamp()<<" :\t"<<a<<"\t|\t"<<b<<"\t";
}

int sc_main(int argc, char* argv[]) {
    tb tb0("tb0");
    FullAdder fa0("fullAdder");

    sc_signal<sc_int<16>> a_sig;
    sc_signal<sc_int<16>> b_sig;
    sc_signal<sc_int<17>> result_sig;

    tb0.a(a_sig);
    tb0.b(b_sig);

    fa0.a(a_sig);
    fa0.b(b_sig);
    fa0.result(result_sig);

    cout<<"a \t:\tb \n";

    //open  vcd file
    sc_trace_file *wf = sc_create_vcd_trace_file("fulladderf");

    sc_trace(wf,a_sig,"a");
    sc_trace(wf,b_sig,"b");
    sc_trace(wf,result_sig,"result");

    sc_start();
    sc_close_vcd_trace_file(wf);

    cout<<"\nthe end";

    return 0;


}
