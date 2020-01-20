#include "cpu2.h"
#include "definitions.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void cpu2::task5() {
    int i = 4;
    int room5;
    for (;;) {
        wait();

        in->read(room5);

        hexs[i].write(room5);
        if (room5 > 0) {
            ledOn(leds.read());
        } else {
            ledOff(leds.read());
        }
    }
}

void cpu2::ledOn(sc_bv<8> l) {
    if (!(l.to_int() & LED5)) {
        wait(500, SC_MS);
    }
    leds.write(l | LED5);
}

void cpu2::ledOff(sc_bv<8> l) {
    if (l.to_int() & LED5) {
        wait(1000, SC_MS);
    }
    leds.write(l & ~LED5);
}

#pragma clang diagnostic pop