#include <iostream>
#include <future>
#include <thread>

void consumer(int id, std::shared_future<int> sf) 
{
    int val = sf.get(); // waits and gets value
    std::cout << "Consumer " << id << " received: " << val << '\n';
}

int main() 
{
    std::promise<int> p;
    std::shared_future<int> sf = p.get_future(); // shared_future created

    // 3 consumer threads
    std::thread t1(consumer, 1, sf);
    std::thread t2(consumer, 2, sf);
    std::thread t3(consumer, 3, sf);

    // Sonucu üretelim
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    p.set_value(42);

    t1.join();
    t2.join();
    t3.join();
}
