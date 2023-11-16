#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

int data;
bool ready_flag{};
std::mutex mtx;
std::condition_variable cv;

void producer()
{
	{
		std::lock_guard lg{mtx};
		data = 2345;
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

	std::cout << "data : " << data;
}

int main()
{
	std::thread t1(producer);
	std::thread t2(consumer);

	t1.join(); t2.join();
}
