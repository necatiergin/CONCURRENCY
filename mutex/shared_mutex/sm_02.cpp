#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>
#include <syncstream>

std::shared_mutex mtx;
int shared_counter = 0;

void reader(int id) 
{
    std::shared_lock lock(mtx);
    std::osyncstream{ std::cout } << "Reader " << id << ": counter = " << shared_counter << "\n";
}

void writer(int id) {

    std::unique_lock lock(mtx);
    ++shared_counter;
    std::osyncstream{ std::cout } << "Writer " << id << ": counter incremented\n";
}

int main() 
{
    std::vector<std::thread> threads;

    // 2 writers, 3 readers
    threads.emplace_back(writer, 1);
    threads.emplace_back(writer, 2);
    threads.emplace_back(reader, 1);
    threads.emplace_back(reader, 2);
    threads.emplace_back(reader, 3);

    for (auto& t : threads) 
        t.join();
}
