//quoted from cpprefeence.com

#include <cmath>
#include <future>
#include <iostream>
#include <thread>

int main()
{
    std::packaged_task<int(int, int)> task([](int a, int b)
        {
            return std::pow(a, b);
        });
    std::future<int> result = task.get_future();
    task(2, 9);
    std::cout << "2^9 = " << result.get() << '\n';

    task.reset();
    result = task.get_future();
    std::thread task_td(std::move(task), 2, 10);
    task_td.join();
    std::cout << "2^10 = " << result.get() << '\n';
}
