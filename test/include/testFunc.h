#pragma once
#include <iostream>
#include "InstrumentationTimer.h"
#include <thread>

void function1() {
    PROFILE_FUNCTION();
    //std::cout << "Function1 # " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void function2() {
    PROFILE_FUNCTION();
    //std::cout << "Function2 # " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    function1();
}