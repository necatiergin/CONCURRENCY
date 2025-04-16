#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

void thread_func() 
{
    std::unique_lock<std::mutex> lock(mtx, std::try_to_lock); // ctor tries to lock the mutex

    if (lock.owns_lock()) {
        std::cout << "Mutex locked.\n";
    }
    else {
        std::cout << "Mutex is already locked by another thread.\n";
    }
}

int main() 
{
    mtx.lock(); 
    std::thread t(thread_func);
    t.join();
    mtx.unlock();
}
