#include <thread>
#include <iostream>

thread_local int ival = 0;

void thread_func(int* p) 
{
    *p = 42;
    std::cout << "ival = " << ival << "\n";
}

int main() 
{
    std::cout << "ival = " << ival << "\n";
    ival = 9;
    std::cout << "ival = " << ival << "\n";
    std::thread t(thread_func, &ival);
    t.join();
    std::cout << "ival = " << ival << "\n";
}
