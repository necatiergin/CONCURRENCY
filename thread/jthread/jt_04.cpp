#include <iostream>
#include <thread>
#include <chrono>

using namespace std::literals::chrono_literals;

void f(std::stop_token stop_token)
{
    while (!stop_token.stop_requested())
    {
        std::cout.put('.');
        std::this_thread::sleep_for(10ms);
    }
    std::cout << "\n f is still running!\n";
}

int main()
{
    std::jthread jt(f); // 
    std::this_thread::sleep_for(5s);

    jt.request_stop();
}
