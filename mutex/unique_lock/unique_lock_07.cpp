#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

void foo() 
{
    std::unique_lock lock(mtx);  // locks the mutex
    std::cout << "Mutex mutex locked\n";

    auto pmutex = lock.release();  // lock doesn't own the mutex anymore
    std::cout << "mutex is released.\n";
    std::cout << "unique_lock released the ownership. Mutex is still locked.\n";

    // some code here
    pmutex->unlock(); //// mutex is unlocked
    std::cout << "mutex is unlocked.\n";
}

int main() 
{
    std::jthread jt(foo);
}
