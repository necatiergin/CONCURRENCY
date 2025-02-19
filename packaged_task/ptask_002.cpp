#include <iostream>
#include <future>
#include <thread>
#include <stdexcept>

void foo() 
{
    throw std::runtime_error("runtime error!");
}

int main() 
{
    std::packaged_task<void()> task(foo);
    std::future<void> result = task.get_future();

    std::thread t(std::move(task));
    t.join();

    try {
        result.get();
    }
    catch (const std::exception& ex) {
        std::cout << "exception caught: " << ex.what() << '\n';
    }
}
