#include <thread>
#include <iostream>

int main()
{
    std::cout << "desteklenen donanim thread sayisi : " <<
        std::thread::hardware_concurrency() << '\n';
}
