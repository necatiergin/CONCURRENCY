#include <iostream>
#include <mutex>

int main() 
{
    std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx); // mutex hemen kilitlenir

    std::cout << "Mutex locked by constructor\n";
}
