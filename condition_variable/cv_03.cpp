#include <mutex>
#include <iostream>
#include <chrono>

int shared_variable{};
std::mutex mtx;

void producer()
{
	using namespace std::literals;

	std::this_thread::sleep_for(1000ms);
	std::lock_guard lk{ mtx };

	// ... production code

	shared_variable = 999;
}

void consumer()
{
	using namespace std::literals;
	std::unique_lock ulock{ mtx };
	while (shared_variable == 0)
	{
		ulock.unlock();
		std::this_thread::yield();
		std::this_thread::sleep_for(1000ms);
		ulock.lock();
	}
	
	std::cout << "the value is : " << shared_variable << '\n';
}

int main()
{
	std::thread t1{ producer };
	std::thread t2{ consumer };
	t1.join();
	t2.join();
}
