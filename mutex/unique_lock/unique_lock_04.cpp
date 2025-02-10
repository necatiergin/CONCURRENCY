#include <mutex>
#include <chrono>
#include <iostream>
#include <vector>

std::timed_mutex mtx;

void f() 
{
    using namespace std::literals;
    constexpr auto dur = 5us;
    std::unique_lock lock(mtx, std::defer_lock);
    if (lock.try_lock_for(dur)) {
        std::cout << "mutex kilitlendi thread_id : " << std::this_thread::get_id() << '\n';
        // ... korunan koda erişim ...
    }
    else {
        std::cout << "mutex kilitlenemedi thread_id : " << std::this_thread::get_id() << '\n';
    }
}

int main() 
{
    constexpr std::size_t num_of_threads{ 16 };
    std::vector<std::jthread> tvec{ num_of_threads };

    for (std::size_t i{}; i < tvec.size(); ++i)
        tvec[i] = std::jthread{ f };
}
