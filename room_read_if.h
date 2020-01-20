#ifndef SW_PROJEKT_ROOM_READ_IF_H
#define SW_PROJEKT_ROOM_READ_IF_H

#include <systemc.h>

class room_read_if: virtual public sc_interface {
public:
    virtual bool read(int &) = 0;
protected:
    room_read_if(){ };
private:
    room_read_if (const room_read_if&); // disable copy
};

#endif //SW_PROJEKT_ROOM_READ_IF_H
