#include <iostream>
#include <thread>
#include <chrono>
#include <stop_token>

void worker(std::stop_token stoken) 
{
    while (!stoken.stop_requested()) {
        std::cout << "thread is running...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << "thread is being stopped...\n";
}

int main() 
{
    std::stop_source ssource; 
    std::stop_token stoken = ssource.get_token(); 

    std::jthread t(worker, stoken); 
    std::this_thread::sleep_for(std::chrono::seconds(3)); 

    std::cout << "main thread is stopping the child thread...\n";
    ssource.request_stop(); 
}
