//future<T>::wait_for

//from cppreference.com

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

int main()
{
    std::future<int> future = std::async(std::launch::async, []()
        {
            std::this_thread::sleep_for(3s);
            return 8;
        });

    std::cout << "waiting...\n";
    std::future_status status;

    do
    {
        switch (status = future.wait_for(500ms); status)
        {
        case std::future_status::deferred:
            std::cout << "deferred\n";
            break;
        case std::future_status::timeout:
            std::cout << "timeout\n";
            break;
        case std::future_status::ready:
            std::cout << "ready!\n";
            break;
        }
    } while (status != std::future_status::ready);

    std::cout << "result is " << future.get() << '\n';
}
