#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic<int> gcount{ 0 };

void increment() 
{
    int old_value;
    do {
        old_value = gcount.load(); 
    } while (!gcount.compare_exchange_strong(old_value, old_value + 1)); 
}

int main() 
{
    {
        std::vector<std::jthread> tvec;
        for (int i = 0; i < 16; ++i) {
            tvec.emplace_back(increment);
        }
    }

    std::cout << "gcount = " << gcount << '\n';
}
