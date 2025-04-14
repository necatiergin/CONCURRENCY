// start signal

#include <future>
#include <iostream>

void wait_for_go(std::future<void> f) 
{
    f.wait(); // start signal is expected from another thread
    std::cout << "signal received!\n";
}

int main() 
{
    std::promise<void> p;
    std::future<void> f = p.get_future();

    std::thread t(wait_for_go, std::move(f));

    std::this_thread::sleep_for(std::chrono::seconds(1));
    p.set_value(); // start signal

    t.join();
}
