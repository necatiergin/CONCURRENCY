#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>
#include <syncstream>

std::shared_mutex data_mtx;
std::vector<int> data;

void reader(int id) 
{
    std::osyncstream ocout{ std::cout };

    for (int i = 0; i < 5; ++i) {
        std::shared_lock read_lock(data_mtx); 
        ocout << "reader " << id << ": ";
        for (int val : data) {
            ocout << val << ' ';
        }
        ocout.put('\n');
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
    }
}

void writer() 
{
    std::osyncstream ocout{ std::cout };

    for (int i = 0; i < 3; ++i) {
        std::unique_lock<std::shared_mutex> writeLock(data_mtx); 
        ocout << "writing : " << i << '\n';
        data.push_back(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
    }
}

int main() 
{
    std::jthread t1(writer);
    std::jthread t2(reader, 1);
    std::jthread t3(reader, 2);
    std::jthread t4(reader, 3);
    std::jthread t5(reader, 4);
}
