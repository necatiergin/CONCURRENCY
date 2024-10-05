#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::literals;

std::timed_mutex tmtx;

void foo_task()
{
	std::cout << "foo_task trying to lock the mutex\n";
	tmtx.lock();
	std::cout << "foo_task locks the mutex\n";
	std::this_thread::sleep_for(5s);
	std::cout << "foo_task unlocking the mutex\n";
	tmtx.unlock();
}

void bar_task()
{
	std::this_thread::sleep_for(200ms);
	std::cout << "bar_task is trying to lock the mutex\n";

	while (!tmtx.try_lock_for(500ms)) {
		std::cout << "bar_task could not lock the mutex\n";
	}

	std::cout << "bar_task has locked the mutex\n";

	tmtx.unlock();
}

int main()
{
	std::thread thr1(foo_task);
	std::thread thr2(bar_task);

	thr1.join(); 
	thr2.join();
}
