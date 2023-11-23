#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

int gdata;
bool ready_flag{};
std::mutex mtx;
std::condition_variable cv;

void producer()
{
	{
		std::lock_guard lg{ mtx };
		gdata = 2345;
		ready_flag = true;
	}
	cv.notify_one();
}

void consumer()
{
	{
		std::unique_lock lock{ mtx };
		cv.wait(lock, [] {return ready_flag; });
	}

	std::cout << "gdata : " << gdata;
}

int main()
{
	std::jthread t1(producer);
	std::jthread t2(consumer);
}
