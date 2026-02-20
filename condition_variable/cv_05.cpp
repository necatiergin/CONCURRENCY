#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>
#include <syncstream> 

std::condition_variable cv;
std::mutex mtx;
int shared_value = 0; // The shared condition 

using namespace std::literals;

// The thread function that waits for the condition to be met
void waiter_thread(const std::string& thread_id)
{
	// Acquire a unique lock on the mutex
	std::unique_lock<std::mutex> lock(mtx);

	std::cout << thread_id << " is waiting\n";

	// Wait until the shared_value is 1.
	// This atomically unlocks the mutex and blocks the thread.
	// When notified, it re-acquires the mutex and checks the predicate (gval == 1).
	cv.wait(lock, [&] { return shared_value == 1; });

	// The condition is met, the thread continues execution
	std::cout << thread_id << " finished waiting. shared_value == 1\n";
}

// The thread function that signals the waiting threads
void signaler_thread(const std::string& thread_id)
{
	// Wait for 1 second to allow waiters to block
	std::this_thread::sleep_for(1s);

	std::osyncstream{ std::cout } << thread_id << " first notification (shared_value is still 0)\n";

	// 1st notify_all: Signals all waiting threads. 
	// Since shared_value is 0, the waiters will wake up, check the predicate, 
	// find it false, and go back to sleep (spurious wakeup handled by predicate).
	cv.notify_all();

	// Short delay after the first notification
	std::this_thread::sleep_for(std::chrono::seconds(1s));

	{
		// Lock the mutex to safely modify the shared variable
		std::lock_guard<std::mutex> lock(mtx);
		shared_value = 1; // Change the condition
		std::cout  << thread_id << " shared_value updated to 1, notifying again\n";
	} // Mutex is released here as lock_guard goes out of scope

	// 2nd notify_all: Signals all waiting threads again.
	// Since shared_value is now 1, the woken waiters will check the predicate, 
	// find it true, and exit the wait state.
	cv.notify_all();
}

int main()
{
	std::jthread
		t1(waiter_thread, "t1"),
		t2(waiter_thread, "t2"),
		t3(waiter_thread, "t3"),
		t4(signaler_thread, "t4"),
		t5(signaler_thread, "t5");
}
