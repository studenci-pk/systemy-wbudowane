#ifndef SW_PROJEKT_CPU_H
#define SW_PROJEKT_CPU_H

#include <systemc.h>
#include "room_channel.h"
#include "definitions.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

#define LED_ON 2000
#define LED_OFF 1000

#define ERR_ON 3000
#define ERR_OFF 2000

SC_MODULE(cpu1) {
private:
    struct input_event ev;
    sc_event room_event;
    ssize_t n;
    volatile int _leds;
    int s[5];
    int fd;
    int setup();
    const char* decoder(sc_bv<7> vec);
    bool getKey(int &code);
    void ledOn(int led);
    void ledOff(int led);
public:
    sc_in_clk clk;
    sc_port<room_write_if> out;
    sc_inout<sc_bv<8>> leds;
    sc_inout<sc_bv<7>> hexs[ROOMS];

    void task1();
    void task2();
    void task3();
    void task4();

    void display();
    void printToFile();

    SC_CTOR(cpu1) : room_event("room_event"), s{0, 0, 0, 0, 0} {
        SC_THREAD(task1);
        sensitive << clk.pos() << clk.neg();
        SC_THREAD(task2);
        sensitive << room_event << clk.pos();
        SC_THREAD(task3);
        sensitive << room_event << clk.pos();
        SC_THREAD(task4);
        sensitive << room_event << clk.pos();

//        SC_METHOD(display);
//        dont_initialize();
//        sensitive << leds.value_changed_event();
    }
};


#endif //SW_PROJEKT_CPU_H
