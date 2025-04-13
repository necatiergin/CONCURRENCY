// native handle

#include <iostream>
#include <thread>
#include <windows.h>

void foo() 
{
    std::cout << "Thread is running with modified priority!\n";
}

int main() 
{
    std::thread t(foo);

    auto handle = t.native_handle();

    if (SetThreadPriority(handle, THREAD_PRIORITY_HIGHEST)) {
        std::cout << "Thread priority set successfully\n";
    }
    else {
        std::cerr << "Failed to set thread priority\n";
    }

    t.join();
}
