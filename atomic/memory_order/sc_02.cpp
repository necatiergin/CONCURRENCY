#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> x{ 0 };
std::atomic<int> y{ 0 };
int r1, r2;

void foo() 
{
    x.store(1, std::memory_order_seq_cst);  // x = 1
    r1 = y.load(std::memory_order_seq_cst); // r1 = y
}

void bar() {
    y.store(1, std::memory_order_seq_cst);  // y = 1
    r2 = x.load(std::memory_order_seq_cst); // r2 = x
}

int main() 
{
    for (int i = 0; i < 1000; ++i) {
        x = 0;
        y = 0;
        std::thread t1(foo);
        std::thread t2(bar);
        t1.join();
        t2.join();

        if (r1 == 0 && r2 == 0) {
            std::cout << "none of the threads has seen the write operation\n!";
        }
    }
   }
