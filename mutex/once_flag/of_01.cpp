#include <iostream>
#include <mutex>
#include <thread>

std::once_flag init_flag;

void init()
{
    std::cout << "init called\n";
}

void foo()
{
    std::call_once(init_flag, init);
    std::cout << "foo running\n";
}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    std::thread t3(foo);

    t1.join();
    t2.join();
    t3.join();
}
