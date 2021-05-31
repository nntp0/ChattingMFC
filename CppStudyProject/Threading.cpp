#include "Threading.h"
#include <iostream>
#include <thread>



void Threading::run() {
    std::thread t1(counter, 1, 6);

    t1.join();
}

void counter(int id, int numIterations) {
    for (int i = 0; i < numIterations; i++) {
        std::cout << "Counter " << id << " has value " << i << std::endl;
    }
}