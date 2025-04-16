#include <iostream>
#include <mutex>

int main() 
{
    std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock); // doesn't lock

    std::cout << "mutex is not locked\n";

    lock.lock(); // we lock the mutex
    std::cout << "Mutex is locked now.\n";
}
