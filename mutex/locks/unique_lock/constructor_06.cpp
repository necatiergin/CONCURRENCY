#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

std::timed_mutex tmtx;

void thread_func() 
{

    std::unique_lock<std::timed_mutex> lock(tmtx, std::chrono::milliseconds(500)); 
    // tries to lock for 500ms
    if (lock.owns_lock()) {
        std::cout << "Mutex locked (try_lock_for)\n";
    }
    else {
        std::cout << "time-out(try_lock_for)\n";
    }
}

int main() 
{
    tmtx.lock(); 
    std::thread t(thread_func);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    tmtx.unlock();
    t.join();
}
