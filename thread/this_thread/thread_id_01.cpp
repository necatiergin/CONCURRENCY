#include <iostream>
#include <thread>

void print_thread_id() 
{
    std::cout << "Thread ID     : " << std::this_thread::get_id() << '\n';
}

int main() 
{
    std::cout << "main thread ID: " << std::this_thread::get_id() << '\n';

    std::thread t1(print_thread_id);
    std::thread t2(print_thread_id);

    t1.join();
    t2.join();
}
