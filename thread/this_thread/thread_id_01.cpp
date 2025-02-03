// std::this_thread::get_id() in C++ returns the ID of the current thread.
// Each thread has a unique identifier, which is useful for debugging, logging, or managing multiple threads.
// It returns a std::thread::id object.
// The ID helps distinguish different threads in multi-threaded programs.

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
