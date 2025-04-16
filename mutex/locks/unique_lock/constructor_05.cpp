#include <iostream>
#include <mutex>

int main() 
{
    std::mutex mtx;
    mtx.lock(); // we lock the mutex manually

    std::unique_lock<std::mutex> lock(mtx, std::adopt_lock); // we own the locked mutex
    std::cout << "mutex adopted.\n";
}
