#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::literals;

std::mutex mtx;

void foo_task()
{
	std::cout << "foo_task trying to lock the mutex\n";
	mtx.lock();
	std::cout << "foo_task has locked the mutex\n";
	std::this_thread::sleep_for(800ms);
	std::cout << "foo_task unlocking the mutex\n";
	mtx.unlock();
}

void bar_task()
{
	std::this_thread::sleep_for(100ms);
	std::cout << "bar_task trying to lock the mutex\n";
	while (!mtx.try_lock()) {
		std::cout << "bar_task could not lock the mutex\n";
		std::this_thread::sleep_for(100ms);
	}
	std::cout << "bar_task has locked the mutex\n";
	mtx.unlock();
}

int main()
{
	std::thread tfoo(foo_task);
	std::thread tbar(bar_task);

	tfoo.join();
	tbar.join();
}
