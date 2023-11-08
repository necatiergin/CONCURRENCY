#include <iostream>
#include <syncstream>
#include <string>
#include <thread>
#include <mutex>

thread_local int tval{ 0 };

void func(const std::string& thread_name)
{
    ++tval; //senkronizasyon gerekmiyor
    std::osyncstream{std::cout} << "tval in thread " << thread_name << " is " << tval << "\n";
}

int main()
{
    std::thread tx(func, "a");
    std::thread ty(func, "b");

    {
        std::osyncstream{ std::cout } << "tval in main: " << tval << '\n';
    }

    tx.join();
    ty.join();
}
