#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
using namespace literals;

std::mutex mtx;

void foo()
{
	cout << "foo is trying to lock the mutex\n";
	mtx.lock();
	std::cout << "foo has locked the mutex\n";
	this_thread::sleep_for(800ms);
	cout << "foo is unlocking the mutex\n";
	mtx.unlock();
}

void bar()
{
	this_thread::sleep_for(100ms);
	cout << "bar trying to lock the mutex\n";
	while (!mtx.try_lock()) {
		cout << "bar could not lock the mutex\n";
		this_thread::sleep_for(100ms);
	}
	cout << "bar has locked the mutex\n";
	mtx.unlock();
}

int main()
{
	std::jthread thr1(foo);
	std::jthread thr2(bar);
}
