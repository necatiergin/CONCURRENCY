#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>
#include <chrono>

std::mutex mtx;
std::condition_variable cv;

using namespace std::chrono_literals;

void waiter_thread()
{
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "waiter: going to wait...\n";
    // BUG: The code is missing a predicate
    // shared condition to check before waiting
    cv.wait(lock);
    std::cout << "waiter: woke up!\n";
}

void notifier_thread()
{
    // Delay slightly so we can observe the scenario more reliably
    std::this_thread::sleep_for(10ms);

    std::cout << "notifier: notifying...\n";
    cv.notify_one();
}

int main()
{
    std::thread notifier_t(notifier_thread);

    // TIMING IS CRITICAL HERE:
    // If the waiter enters wait() AFTER the notifier calls notify_one(), 
    // a lost wakeup occurs.
    // Delay to intentionally create a timing issue for demonstration
    std::this_thread::sleep_for(50ms);
    std::thread waiter_t(waiter_thread);

    notifier_t.join();
    waiter_t.join();
}
