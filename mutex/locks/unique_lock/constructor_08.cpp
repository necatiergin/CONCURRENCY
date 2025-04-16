#include <iostream>
#include <mutex>

int main() 
{
    std::mutex mtx;
    std::unique_lock<std::mutex> lock1(mtx);

    std::unique_lock<std::mutex> lock2(std::move(lock1)); 

    if (!lock1.owns_lock()) 
        std::cout << "lock1 doesn't own the mutex.\n";
    
    if (lock2.owns_lock()) 
        std::cout << "lock2 owns the mutex.\n";
}
