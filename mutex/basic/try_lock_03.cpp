#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>


using namespace std::literals;
std::mutex mtx;

void foo()
{
	std::cout << "foo is trying to lock the mutex\n";
	mtx.lock();
	std::cout << "foo has locked the mutex\n";
	std::this_thread::sleep_for(800ms);
	std::cout << "foo is unlocking the mutex\n";
	mtx.unlock();
}

void bar()
{
	std::this_thread::sleep_for(100ms);
	std::cout << "bar trying to lock the mutex\n";
	while (!mtx.try_lock()) {
		std::cout << "bar could not lock the mutex\n";
		std::this_thread::sleep_for(100ms);
	}
	std::cout << "bar has locked the mutex\n";
	mtx.unlock();
}

int main()
{
	std::jthread thr1(foo);
	std::jthread thr2(bar);
}
