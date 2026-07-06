#include <iostream>
#include <thread>

int main()
{
    auto n = std::thread::hardware_concurrency();

    if (n == 0) {
        std::cout << "hardware concurrency bilgisi elde edilemedi\n";
    }
    else {
        std::cout << "hardware concurrency = " << n << '\n';
    }
}
