#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

std::timed_mutex tmtx;

void thread_func() 
{
    auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(1);
    std::unique_lock<std::timed_mutex> lock(tmtx, deadline);

    if (lock.owns_lock()) {
        std::cout << "Mutex locked (try_lock_until)\n";
    }
    else {
        std::cout << "time-out(try_lock_until)\n";
    }
}

int main() 
{
    tmtx.lock(); 
    std::thread t(thread_func);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    tmtx.unlock();
    t.join();
}
