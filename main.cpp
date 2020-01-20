#include <systemc.h>
#include <cstdio>
#include <vector>
#include "room_channel.h"
#include "cpu1.h"
#include "cpu2.h"
#include "definitions.h"

int sc_main(int, char* []) {

    sc_core::sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", sc_core::SC_DO_NOTHING);

    sc_clock clk1("clk1", 10, SC_MS, 0.5);
    sc_signal<bool> reset(0); // sc_bit is deprecated
    sc_signal<sc_bv<8>, SC_MANY_WRITERS> leds("led_sign");
    sc_signal<sc_bv<7>, SC_UNCHECKED_WRITERS> hexs[ROOMS];

    room_channel channel; // kanał prosty

    cpu1 main_cpu("cpu1inst");

    //podpięcie sygnałów
    main_cpu.clk(clk1);
    main_cpu.out(channel);
    main_cpu.leds(leds);
    for (int i = 0; i < ROOMS; i++) {
        main_cpu.hexs[i](hexs[i]);
    }

    cpu2 secondary_cpu("cpu2inst");
    secondary_cpu.clk(clk1);
    secondary_cpu.in(channel);
    secondary_cpu.leds(leds);
    for (int i = 0; i < ROOMS; i++) {
        secondary_cpu.hexs[i](hexs[i]);
    }

    sc_start(); // symulacja nieskończona

    return EXIT_SUCCESS;
}