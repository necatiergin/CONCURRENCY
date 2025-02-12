#include <mutex>
#include <iostream>
#include <chrono>

int shared_variable{};
std::mutex mtx;

using namespace std::literals;

void producer()
{
	std::this_thread::sleep_for(1000ms);
	std::lock_guard lg{ mtx };

	// ... production code

	shared_variable = 999;
}

void consumer()
{
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
	std::jthread t1{ producer };
	std::jthread t2{ consumer };
}
