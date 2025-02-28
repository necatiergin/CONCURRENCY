#include <atomic>
#include <thread>
#include <iostream>
#include <cassert>

std::atomic<bool> x, y, z;


void foo()
{
    x.store(true, std::memory_order_relaxed);
}

void bar()
{
    y.store(true, std::memory_order_relaxed);
}

void baz()
{

    while (!y.load(std::memory_order_relaxed))
        ;

    if (x.load(std::memory_order_relaxed)) {
        z = true;
    }

    assert(z);
}

int main()
{
    for (int i = 0; i < 100000; ++i) {
        x = false;
        y = false;
        z = false;
        std::jthread thread_1(foo);
        std::jthread thread_2(bar);
        std::jthread thread_3(baz);
    }
}
