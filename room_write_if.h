#ifndef SW_PROJEKT_ROOM_WRITE_IF_H
#define SW_PROJEKT_ROOM_WRITE_IF_H

#include <systemc.h>

class room_write_if: virtual public sc_interface {
public:
    virtual bool write(int) = 0;
    virtual void reset() = 0; // empty the stack
protected:
    room_write_if(){ };
private:
    room_write_if (const room_write_if&);      // disable copy
};

#endif //SW_PROJEKT_ROOM_WRITE_IF_H
