#include <iostream>
#include <thread>
#include <vector>
#include <semaphore>
#include <chrono>
#include <syncstream>

std::counting_semaphore<3> resource_pool(3);

void worker_thread(int id) 
{
    resource_pool.acquire();

    std::osyncstream(std::cout) << "Thread " << id << " is using the resource.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::osyncstream(std::cout) << "Thread " << id << " is releasing the resource.\n";

    resource_pool.release();
}

int main() 
{
    std::vector<std::thread> workers;

    for (int i = 0; i < 10; ++i) {
        workers.emplace_back(worker_thread, i);
    }

    for (auto& t : workers) {
        t.join();
    }
}
