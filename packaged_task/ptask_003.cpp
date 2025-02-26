#include <thread>
#include <functional>
#include <future>
#include <iostream>


int sum(int a, int b)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return a + b;
}

int main()
{
    int x = 10;
    int y = 20;

    // some code here

    std::packaged_task<int()> task(std::bind(sum, x, y));

    std::future<int> result = task.get_future();

    std::thread t(std::move(task));

    std::cout << "result is: " << result.get() << '\n';

    t.join();
}
