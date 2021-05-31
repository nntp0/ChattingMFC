#include "Threading.h"
#include <iostream>
#include <thread>

bool Threading::finished = false;

void Threading::run() {
    std::thread t1(workForFirst);
    std::thread t2(workForSecond);

    t1.join();
    t2.join();
}

void counter(int id, int numIterations) {
    for (int i = 0; i < numIterations; i++) {
        std::cout << "Counter " << id << " has value " << i << std::endl;
    }
}

void workForFirst() {
    for (int i = 0; i < 3; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Thread 1";
    }
    Threading::finished = true;
}

void workForSecond() {
    while(!Threading::finished) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Thread 2";
    }
}