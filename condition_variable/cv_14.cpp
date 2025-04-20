#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

bool predicate()
{
    std::cout << "[Predicate] Checking condition (ready == " << std::boolalpha << ready << ")\n";
    return ready;
}

void waiting_thread() 
{
    //std::this_thread::sleep_for(std::chrono::milliseconds(300)); 
    std::this_thread::sleep_for(std::chrono::milliseconds(0)); 
    std::cout << "[WaitingThread] Trying to acquire lock...\n";

    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "[WaitingThread] Lock acquired. Calling wait...\n";

    cv.wait(lock, predicate); 

    std::cout << "[WaitingThread] Woken up. Condition met. Continuing work...\n";
}

void notifier_thread()
{
    std::cout << "[Notifier] Sleeping 100ms before setting condition...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "[Notifier] Lock acquired. Setting ready = true.\n";
        ready = true;
    }

    std::cout << "[Notifier] Calling notify_one...\n";
    cv.notify_one();
}

int main()
{
    std::thread t1(waiting_thread);
    std::thread t2(notifier_thread);

    t1.join();
    t2.join();
}
