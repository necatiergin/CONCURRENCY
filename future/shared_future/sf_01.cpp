#include <future>
#include <iostream>
#include <thread>
#include <chrono>
#include <syncstream>


void worker(std::shared_future<int> sf, int id)
{
    std::osyncstream{ std::cout } << "Thread " << id << " waiting...\n";

    int value = sf.get();

    std::osyncstream{ std::cout } << "Thread "
        << id
        << " got "
        << value
        << '\n';
}

int main()
{
    std::promise<int> p;

    auto sf = p.get_future().share();

    std::thread t1(worker, sf, 1);
    std::thread t2(worker, sf, 2);
    std::thread t3(worker, sf, 3);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    p.set_value(42);

    t1.join();
    t2.join();
    t3.join();
}
