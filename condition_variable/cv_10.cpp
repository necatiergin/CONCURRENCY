#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker(int id) 
{
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "[Worker " << id << "] Waiting for condition...\n";

    cv.wait(lock, [] { return ready; }); 

    std::cout << "[Worker " << id << "] Condition met, working...\n";
}

void notifier() 
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "[Notifier] Setting ready = true.\n";
        ready = true;
    }

    std::cout << "[Notifier] Calling notify_all().\n";
    cv.notify_all();
}


int main() 
{
    std::vector<std::thread> threads;

    for (int i = 0; i < 8; ++i) {
        threads.emplace_back(worker, i + 1);
    }

    std::thread t(notifier);

    for (auto& th : threads) 
        th.join();

    t.join();
}
