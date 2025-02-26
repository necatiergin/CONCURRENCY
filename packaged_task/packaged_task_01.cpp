#include <iostream>
#include <future>
#include <thread>
#include <chrono>

int sum(int a, int b) 
{
    std::this_thread::sleep_for(std::chrono::seconds(2)); 
    return a + b;
}

int main() 
{
    std::packaged_task<int(int, int)> task(sum);

    std::future<int> result = task.get_future();

    std::thread t(std::move(task), 10, 20);

    std::cout << "result is: " << result.get() << '\n';

    t.join();
}
