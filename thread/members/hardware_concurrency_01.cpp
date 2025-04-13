#include <thread>
#include <iostream>

int main()
{
    std::cout << "hardware supported number of threads is : " <<
        std::thread::hardware_concurrency() << '\n';
}
