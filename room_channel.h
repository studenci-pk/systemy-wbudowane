#ifndef SW_PROJEKT_ROOM_CHANNEL_H
#define SW_PROJEKT_ROOM_CHANNEL_H

#include "room_read_if.h"
#include "room_write_if.h"

class room_channel : public sc_prim_channel, public room_read_if, public room_write_if {
private:
    sc_event data_read_event;
    sc_event data_written_event;

    int bus;
    bool wr;
    bool rd;

public:
    explicit room_channel() : sc_prim_channel(sc_gen_unique_name("room_channel")) { }
    bool read(int &);
    bool write(int);
    void reset();
    void update();
};


#endif //SW_PROJEKT_ROOM_CHANNEL_H
