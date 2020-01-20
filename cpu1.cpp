#include "cpu1.h"
#include <iostream>
#include <vector>
#include "definitions.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void cpu1::task1() {
    int code;

    std::vector<std::pair<int, int>> doors {{ //(DOORS)
        std::make_pair(3, 4),
        std::make_pair(3, 2),
        std::make_pair(2, 5),
        std::make_pair(5, 0),
        std::make_pair(0, 2),
        std::make_pair(1, 0),
        std::make_pair(4, 1),
        std::make_pair(2, 1)
    }};

//    std::vector<std::pair<int, int>>::iterator it;
//    for (it = doors.begin(); it != doors.end(); ++it) {
//        std::cout << it->first << ", " << it->second << std::endl;
//    }


    setup();
    display();
    printToFile();

    int key;
    int direction = 0;
    _leds = 0;

    for(;;) {

        wait(clk.posedge_event());

        if (getKey(key)) {
            int err = false;
            if (true) { //std::cin >> code
                //printf(">>%d<<\n", key);
                code = key - 1;

                // CALCULATIONS
                if (code >= 1 && code <= DOORS) {
                    int i = code - 1;
                    int r1 = doors[i].first - 1;
                    int r2 = doors[i].second - 1;

                    if (r1 > -1) {
                        s[r1] = direction ? s[r1] + 1 : s[r1] - 1;
                    }

                    if (r2 > -1) {
                        s[r2] = direction ? s[r2] - 1 : s[r2] + 1;
                    }
                    std::cout << s[0] << " " << s[1] << " " << s[2] << " " << s[3] << " " << s[4] << " " << std::endl;
                } else if (code == 15) {
                    sc_stop();

                } else if (code == 16) {
                    direction = !direction;
                    std::cout << (direction ? " <- " : " -> ") << std::endl;
                }

                // NOTIFY TASKS & WRITE TO CHANNEL
                out->write(s[4]);
                room_event.notify();

                // DIRECTION LED
                if (direction) {
                    _leds |= LED0;
                } else {
                    _leds &= ~LED0;
                }

                // ROOM 1
                hexs[0].write(s[0]);
                if (s[0] > 0) {
                    if (!(_leds & LED1)) {
                        wait(LED_ON, SC_MS);
                    }
                    _leds |= LED1;
                }  else {
                    if (_leds & LED1) {
                        wait(LED_OFF, SC_MS);
                    }
                    _leds &= ~LED1;
                }

                //LED ERROR
                for (int i = 0; i < ROOMS; i++) {
                    if (s[i] < 0) {
                        err = true;
                    }
                }

                if(err) {
                    if (!(_leds & LED7)) {
                        wait(ERR_ON, SC_MS);
                    }
                    _leds |= LED7;
                } else {
                    if (_leds & LED7) {
                        wait(ERR_OFF, SC_MS);
                    }
                    _leds &= ~LED7;
                }

//                // Write to leds
//                wait(clk.negedge_event());
//                leds.write(_leds | (leds.read() & LED5));
//                std::cout << leds.read() << std::endl;

//            if (s[0] > 0) {
//                ledOn(LED1);
//            } else {
//                ledOff(LED1);
//            }
            }
        }

        // Write to leds
        wait(clk.negedge_event());
        leds.write(_leds | (leds.read() & LED5));

//        display();
//        std::cout << _leds  << " " << leds.read() << std::endl;
        printToFile();
    }
}

void cpu1::task2() {
    int i = 1;
    for (;;) {
        wait(room_event);

        hexs[i].write(s[i]);
        if (s[i] > 0) {
            if (!(_leds & LED2)) {
                wait(LED_ON, SC_MS);
            }

            _leds |= LED2;
        } else {
            if (_leds & LED2) {
                wait(LED_OFF, SC_MS);
            }
            _leds &= ~LED2;
        }


//        if (s[i] > 0) {
//            ledOn(LED2);
//        } else {
//            ledOff(LED2);
//        }
//        wait(10, SC_MS);
    }
}

void cpu1::task3() {
    int i = 2;
    for (;;) {
        wait(room_event);

        hexs[i].write(s[i]);
        if (s[i] > 0) {
            if (!(_leds & LED3)) {
                wait(LED_ON, SC_MS);
            }
            _leds |= LED3;
        } else {
            if (_leds & LED3) {
                wait(LED_OFF, SC_MS);
            }
            _leds &= ~LED3;
        }

//        if (s[i] > 0) {
//            ledOn(LED3);
//        } else {
//            ledOff(LED3);
//        }
//        wait(10, SC_MS);
    }
}

void cpu1::task4() {
    int i = 3;
    for (;;) {
        wait(room_event);

        hexs[i].write(s[i]);
        if (s[i] > 0) {
            if (!(_leds & LED4)) {
                wait(LED_ON, SC_MS);
            }
            _leds |= LED4;
        } else {
            if (_leds & LED4) {
                wait(LED_OFF, SC_MS);
            }
            _leds &= ~LED4;
        }

//        if (s[i] > 0) {
//            ledOn(LED4);
//        } else {
//            ledOff(LED4);
//        }
//        wait(10, SC_MS);
    }
}

void cpu1::display() {
    sc_bv<8> l = leds.read();

    std::cout << std::endl << (l.get_bit(0) ? "+" : "-") << " ";
    for (int i = 1; i < l.length(); i++) {
        std::cout << (l.get_bit(i) ? "o" : "x") << " ";
    } std::cout << std::endl;

    for(int i = 0; i < ROOMS; i++) {
        std::cout << " (" << hexs[i] << "), ";
        std::cout << "" << decoder(hexs[i]) << "";
    }
    std::cout << std::endl;
}

void cpu1::printToFile() {
    sc_bv<8> l = leds.read();

    ofstream out;
    out.open("/home/przemek/CLionProjects/sw_projekt/output.txt", ios::in); //  | ios::trunc

    out << "LED -> " << (l.get_bit(0) ? "+" : "-") << " ";
    for (int i = 1; i < l.length(); i++) {
        out << (l.get_bit(i)?"o":"x") << " ";
    } out << std::endl;

    out << "HEX -> ";
    for(int i = 0; i < ROOMS; i++) {
//        out << " (" << hexs[i] << "), ";
        out << "" << decoder(hexs[i]) << " ";
    }
    out << std::endl;

    bool err = false;
    for(int i = 0; i < ROOMS; i++) {
        out << "ROOM" << i+1 << ": " << s[i] << "" << std::endl;
        if (s[i] < 0) {
            err = true;
        }
    }

    if (err) {
        out << "ERROR";
    } else {
        out << " \n \n \n \n ";
    }

    out.close();
}

const char* cpu1::decoder(sc_bv<7> vec) {
    switch (vec.to_int()) {
        case 0:
            return "0";
        case 1:
            return "1";
        case 2:
            return "2";
        case 3:
            return "3";
        case 4:
            return "4";
        case 5:
            return "5";
        case 6:
            return "6";
        case 7:
            return "7";
        case 8:
            return "8";
        case 9:
            return "9";
        case 10:
            return "A";
        case 11:
            return "B";
        case 12:
            return "C";
        case 13:
            return "D";
        case 14:
            return "E";
        case 15:
            return "F";
        default:
            if (vec.to_int() > 0) {
                return "o";
            } else {
                return "-";
            }
    }
}


void cpu1::ledOn(int led) {
    sc_bv<8> l = leds.read();
    leds.write(l | led);
}

void cpu1::ledOff(int led) {
    sc_bv<8> l = leds.read();
    leds.write(l & ~led);
}

int cpu1::setup() {
    const char *dev = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";

    fd = open(dev, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
        return EXIT_FAILURE;
    }

    long flag = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}

bool cpu1::getKey(int &code) {
    static const int KEY_PRESSED = 1;

    n = read(fd, &ev, sizeof ev);

    usleep(1000*10); //10ms

    if (n == (ssize_t) -1) {
        if (errno == EINTR)
            return false; // Interrupted system call
        else if (errno == EAGAIN)
            return false; // Try again
        else
            return false;
    } else if (n != sizeof ev) {
        errno = EIO;
        return false;
    }

//    if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2) {
//        code = ev.code;
//        return true;
//    }

    if (ev.type == EV_KEY && ev.value == KEY_PRESSED) {
        code = ev.code;
        return true;
    }

    return false;
}

#pragma clang diagnostic pop