#ifndef SW_PROJEKT_SEC_H
#define SW_PROJEKT_SEC_H

#include <systemc.h>
#include "room_channel.h"
#include "definitions.h"

SC_MODULE(cpu2) {
private:
    void ledOn(sc_bv<8> l);
    void ledOff(sc_bv<8> l);
public:
    sc_in_clk clk;
    sc_port<room_read_if> in;
    sc_inout<sc_bv<8>> leds;
    sc_inout<sc_bv<7>> hexs[ROOMS];

    void task5();

    SC_CTOR(cpu2) {
        SC_CTHREAD(task5, clk.pos());
    }
};


#endif //SW_PROJEKT_SEC_H
