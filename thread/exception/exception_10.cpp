#include <thread>
#include <stdexcept>
#include <iostream>

class X {
public:
    X() = default;
    X(const X&)
    {
        throw std::runtime_error{ "copy failed" };
    }
};

void func(X){}

int main()
{
    X x;

    try
    {
        std::thread t{ func, x };
    }
    catch (const std::exception& ex)
    {
        std::cout << "exception caught : " << ex.what() << '\n';
    }
}
