//intra assignment delay implementation through adder

#include<systemc.h>
#include<queue>
sc_int<32> out(0);
sc_time fix(2,SC_NS);
sc_time start;
//  design module//

SC_MODULE(adder)
{
    sc_in< sc_int<16> > a;
    sc_in< sc_int<16> > b;
    sc_out< sc_int<32> > outp;


    void add()
    {
        while(1)
        {
            out= a.read() + b.read();
            wait(2,SC_NS);
            outp.write(out);
            wait();
        }
    }


    void show()
    {
        cout<<"||sum  @ "<<sc_time_stamp()<<"\t:\t\t\t"<<outp<<endl;
    }

    SC_CTOR(adder)
    {


        SC_THREAD(add);
        sensitive << a << b;
        dont_initialize();

        SC_METHOD(show);
        sensitive <<outp;
        dont_initialize();

    }
};




// test bench //

SC_MODULE(tb)
{
    sc_out< sc_int<16> > a,b;

    void stimulus()
    {

        a.write(0);
        b.write(0);
        wait(5,SC_NS);

        a.write(5);
        b.write(0);
        wait(2,SC_NS);

        a.write(5);
        b.write(5);
        wait(8,SC_NS);

        a.write(7);
        b.write(8);
        wait(3,SC_NS);

        a.write(9);
        b.write(2);
        wait(5,SC_NS);

        a.write(10);
        b.write(21);
        wait(9,SC_NS);

        a.write(6);
        b.write(2);
        wait(5,SC_NS);

        sc_stop();
    }

    void show()
    {
        cout<<"inputs @"<<sc_time_stamp()<<" :\t"<<a<<"\t|\t"<<b<<"\t";
    }

    SC_CTOR(tb)
    {

        SC_THREAD(stimulus);

        SC_METHOD(show);
        sensitive << a<< b;
    }
};



int sc_main(int argc, char* argv[])
{

    tb tb0("tbinst");
    adder ad("adinst");

    sc_signal< sc_int<16> > a_sig, b_sig;
    sc_signal< sc_int<32> > outp_sig;

    tb0.a(a_sig);
    tb0.b(b_sig);

    ad.a(a_sig);
    ad.b(b_sig);
    ad.outp(outp_sig);

    cout<<"a \t:\tb \n";

    //open  vcd file
    sc_trace_file *wf = sc_create_vcd_trace_file("adderf");

    //dumpm desired signals
    sc_trace(wf,a_sig,"a");
    sc_trace(wf,b_sig,"b");
    sc_trace(wf,outp_sig,"output");

    sc_start();
    sc_close_vcd_trace_file(wf);

    cout<<"\nthe end";

    return 0;
}
