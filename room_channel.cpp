#include "room_channel.h"

bool room_channel::read(int &data) {
    wr = false;
    rd = true;
    data = bus;
    request_update();
}

bool room_channel::write(int data) {
    wr = true;
    rd = false;
    bus = data;
    request_update();
}

void room_channel::reset() {
    wr = true;
    rd = false;
    bus = 0;
    request_update();
}

void room_channel::update() {
    if (rd) {
        data_read_event.notify(SC_ZERO_TIME);
        rd = false;
    }
    if (wr) {
        data_written_event.notify(SC_ZERO_TIME);
        wr = false;
    }
}