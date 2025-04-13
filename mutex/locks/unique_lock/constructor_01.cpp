#include <iostream>
#include <mutex>

int main() 
{
    std::mutex mtx;
    std::unique_lock<std::mutex> lock; 

    lock = std::unique_lock<std::mutex>(mtx); 
    std::cout << "Mutex locked\n";
}
