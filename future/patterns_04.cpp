// multiple futures

#include <iostream>
#include <thread>
#include <future>
#include <vector>

void worker(int id, std::future<int> fut) 
{
    int x = fut.get();
    std::cout << "Thread " << id << " got value: " << x << '\n';
}

int main() 
{
    constexpr int number_of_threads = 3;
    std::vector<std::promise<int>> promises(number_of_threads);
    std::vector<std::future<int>> futures;
    std::vector<std::thread> threads;

    // create threads for each future
    for (int i = 0; i < number_of_threads; ++i) {
        futures.push_back(promises[i].get_future());
    }

    // start threads for each thread
    for (int i = 0; i < number_of_threads; ++i) {
        threads.emplace_back(worker, i, std::move(futures[i]));
    }

    // set (different) values for each promise
    for (int i = 0; i < number_of_threads; ++i) {
        promises[i].set_value(i * 10);
    }

    for (auto& t : threads) 
        t.join();
}
