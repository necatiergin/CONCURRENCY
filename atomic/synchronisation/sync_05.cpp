#include <atomic>
#include <iostream>
#include <thread>

std::atomic_int x{ 0 };
std::atomic_bool go{ false };

void f1() 
{
    x.store(1, std::memory_order_release);
    go.store(true, std::memory_order_release);
}

void f2() 
{
    while (!go.load(std::memory_order_acquire)) {}
    x.fetch_add(1, std::memory_order_relaxed); // RMW → release sequence 
}

void f3() 
{
    while (x.load(std::memory_order_acquire) != 2) {}
    std::cout << "x = " << x.load(std::memory_order_relaxed) << '\n';
}

int main() 
{
    std::jthread j1(f1), j2(f2), j3(f3);
}
