#include <iostream>
#include <thread>
#include <atomic>
#include <syncstream>

std::atomic<long long> data{45};

void do_work(int id)
{
    std::osyncstream{ std::cout } << "thread id : " << id << " " <<
        data.fetch_add(1, std::memory_order_relaxed) << '\n';
}

int main()
{
    std::jthread jt1{ do_work, 0 };
    std::jthread jt2{ do_work, 1 };
    std::jthread jt3{ do_work, 2 };
    std::jthread jt4{ do_work, 3 };
    std::jthread jt5{ do_work, 4 };
    std::jthread jt6{ do_work, 5 };
    std::jthread jt7{ do_work, 6 };
    std::jthread jt8{ do_work, 7 };
}
