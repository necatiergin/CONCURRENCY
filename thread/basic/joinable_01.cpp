#include <iostream>
#include <thread>
#include <chrono>

void foo()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
    std::cout << std::boolalpha;

    std::thread t;
    std::cout << "is t joinable ? : " << (t.joinable() ? "yes" : "no") << '\n';
    t = std::thread(foo);
    std::cout << "is t joinable ? : " << (t.joinable() ? "yes" : "no") << '\n';
    t.join();
    std::cout << "is t joinable ? : " << (t.joinable() ? "yes" : "no") << '\n';
}
