#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>
#include <syncstream>


std::shared_mutex shared_mtx;
std::vector<int> data = { 1, 2, 3, 4, 5 };

void reader(int thread_id) 
{
    std::osyncstream ocout{ std::cout };
    std::shared_lock lock(shared_mtx);  
    ocout << "Reader " << thread_id << " is reading data: ";
    for (const auto i : data) {
        ocout << i << ' ';
    }
    ocout << '\n';
}  

void writer(int thread_id, int value) 
{
    std::osyncstream ocout{ std::cout };
    std::unique_lock lock(shared_mtx);  
    ocout << "Writer " << thread_id << " is writing data..." << '\n';
    data.push_back(value);
    ocout << "Writer " << thread_id << " has added value: " << value << '\n';
}  

int main() 
{
    std::jthread r1(reader, 1);
    std::jthread w1(writer, 1, 6);
    std::jthread w2(writer, 2, 7);
    std::jthread r2(reader, 2);
    std::jthread r3(reader, 3);
}
