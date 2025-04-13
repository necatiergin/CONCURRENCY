#include <stdexcept>
#include <mutex>
#include <iostream>

std::once_flag flag;

void may_throw()
{
    static int attempt = 0;
    ++attempt;
    if (attempt < 2)
        throw std::runtime_error("Error!");
    
    std::cout << "2nd try. successful!\n";
}

int main()
{
    try { std::call_once(flag, may_throw); }
    catch (...) {}
    try { std::call_once(flag, may_throw); }
    catch (...) {}
}
