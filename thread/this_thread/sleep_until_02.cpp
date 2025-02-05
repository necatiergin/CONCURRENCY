#include <iostream>
#include <thread>
#include <chrono>

void task(int count, int sec) 
{
    auto next_time = std::chrono::system_clock::now();

    while (count--) {
        next_time += std::chrono::seconds(sec);  

        std::cout << "Executing task at: "
            << std::chrono::system_clock::to_time_t(next_time)
            << std::endl;

        std::this_thread::sleep_until(next_time);  
    }
}

int main() 
{
    std::jthread scheduler(task, 10, 1);
}
