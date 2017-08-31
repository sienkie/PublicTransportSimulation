cmake_minimum_required(VERSION 3.6)
project(symulacja)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp classes/Symulacja.cpp classes/Symulacja.h classes/Osoba.cpp classes/Osoba.h classes/Miejsce.cpp classes/Miejsce.h classes/Przystanek.cpp classes/Przystanek.h classes/Spektakl.cpp classes/Spektakl.h classes/Trasa.cpp classes/Trasa.h classes/Pojazd.cpp classes/Pojazd.h classes/Linia.cpp classes/Linia.h classes/Kolejka.cpp classes/Kolejka.h classes/Zdarzenie.cpp classes/Zdarzenie.h)
add_executable(symulacja ${SOURCE_FILES})