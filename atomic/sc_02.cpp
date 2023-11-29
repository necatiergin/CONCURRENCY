#include <atomic>
#include <cassert>
#include <thread>

//foo baz bar func sırasiyla calismis olsunlar
// assertion'lar fail olabilir mi?

std::atomic<int> x{ 0 }, y{ 0 };

void foo()
{
    x.store(1, std::memory_order_seq_cst);
}


void bar()
{
    y.store(1, std::memory_order_seq_cst);
}

void baz()
{
    assert(x.load() == 1 && y.load() == 0);
}


void func()
{
    assert(x.load() == 1 && y.load() == 1);
}

int main()
{
    std::jthread{ foo };
    std::jthread{ baz};
    std::jthread{ bar};
    std::jthread{ func};
}
