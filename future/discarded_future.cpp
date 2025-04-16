#include <iostream>
#include <future>
#include <chrono>

void do_work() 
{
    std::cout << "[do_work] started...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "[do_work] complete.\n";
}

int main() 
{
    std::cout << "[main] async called...\n";

    // std::launch::async return value discarded
    std::async(std::launch::async, do_work);

    std::cout << "[main] async return value discarded.\n";
    
    // main will not run until do_work returns
    std::cout << "[main] this will be seen after do work completed\n";
}
