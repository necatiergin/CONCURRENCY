#include <thread>
#include <string>
#include <syncstream>
#include <iostream>

thread_local int tval{ 0 };

void func(const std::string& thread_name)
{
    ++tval; //senkronizasyon gerekmiyor
    std::osyncstream{ std::cout } << "tval in thread " << thread_name << " is " << tval << "\n";
}

int main()
{
    std::thread ta(func, "a");
    std::thread tb(func, "b");
    std::thread tc(func, "c");
    std::thread td(func, "d");

    {
        std::osyncstream{ std::cout } << "tval in main: " << tval << '\n';
    }

    ta.join();
    tb.join();
    tc.join();
    td.join();
}

