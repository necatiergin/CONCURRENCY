#include <iostream>
#include <thread>
#include <atomic>

// Shared flag to signal thread completion
std::atomic<bool> ready(false);

void worker_thread() 
{
    std::cout << "Worker thread waiting for signal...\n";
    while (!ready.load()) {
        std::this_thread::yield(); // Yield CPU to other threads
    }
    std::cout << "Worker thread proceeding...\n";
}

int main() 
{
    std::thread t(worker_thread);

    // Simulate some work in the main thread
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Set flag to signal worker thread
    ready.store(true);

    // Wait for worker thread to complete
    t.join();

    std::cout << "Main thread finished.\n";
}
