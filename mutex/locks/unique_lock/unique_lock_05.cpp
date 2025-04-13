#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::timed_mutex mtx;

void foo() 
{
    using namespace std::literals;
    {
        std::unique_lock lock(mtx, std::defer_lock);
        auto timeout = std::chrono::steady_clock::now() + 1ms;
        if (lock.try_lock_until(timeout)) {
            std::cout << "Mutex is locked by the thread : " << std::this_thread::get_id() << '\n';
            // some code here...
        }
        else {
            std::cout << "Mutex cannot be locked by the thread: " << std::this_thread::get_id() << '\n';
        }
    }
    std::cout << "Mutex unlocked by the thread: " << std::this_thread::get_id() << '\n';
}

int main() 
{
    std::jthread t1(foo);
    std::jthread t2(foo);
}
