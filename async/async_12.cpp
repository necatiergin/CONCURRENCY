#include <iostream>
#include <future>
#include <chrono>
#include <thread>

void task(const std::string& name) 
{
    std::cout << name << " started on thread " << std::this_thread::get_id() << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << name << " completed\n";
}

int main() 
{
    std::cout << "Main thread ID: " << std::this_thread::get_id() << "\n";

    auto future_async = std::async(std::launch::async, task, "Async Task");
    auto future_deferred = std::async(std::launch::deferred, task, "Deferred Task");

    std::cout << "Waiting 1 second in main...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Calling wait() on async task...\n";
    future_async.wait(); 

    std::cout << "Calling get() on deferred task...\n";
    future_deferred.get(); 

    std::cout << "All tasks finished.\n";
}
