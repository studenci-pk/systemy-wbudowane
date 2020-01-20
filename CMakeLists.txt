cmake_minimum_required(VERSION 3.10)
project(sw_projekt)

set(CMAKE_CXX_STANDARD 11)

find_package(Curses REQUIRED)
find_package(SystemCLanguage CONFIG REQUIRED)
set(CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD})

include_directories(${CURSES_INCLUDE_DIR})

if (Curses_FOUND)
    message(STATUS "OK")
else()
    message(FATAL_ERROR "!")
endif()

add_executable(sw_projekt main.cpp
        room_write_if.h room_read_if.h room_channel.cpp room_channel.h cpu1.cpp cpu1.h cpu2.cpp cpu2.h definitions.h)
target_link_libraries(sw_projekt ${CURSES_LIBRARIES} SystemC::systemc)