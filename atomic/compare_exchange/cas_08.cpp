#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

class Spinlock {
public:
    void lock() 
    {
        bool expected = false;
        while (!flag.compare_exchange_strong(expected, true)) {
            expected = false; // expected'i tekrar false yap
        }
    }

    void unlock()
    {
        flag.store(false); // unlock
    }
private:
    std::atomic<bool> flag{ false };
    // false: unlocked
    // true: locked
};

Spinlock spinlock;
int shared_data = 0;

void increment_shared_data() 
{
    for (int i = 0; i < 10000; ++i) {
        spinlock.lock(); 
        ++shared_data;   
        spinlock.unlock();
    }
}

int main() 
{
    {
        std::vector<std::jthread> threads;
        for (int i = 0; i < 10; ++i) {
            threads.emplace_back(increment_shared_data);
        }
    }

    std::cout << "Shared data: " << shared_data << '\n';
}
