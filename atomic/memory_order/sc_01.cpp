#include <atomic>
#include <iostream>
#include <thread>
#include <cassert>

std::atomic_bool x_flag, y_flag;
std::atomic<int> ival;


void set_x()
{
	x_flag.store(true);
}

void set_y()
{
	y_flag.store(true);
}

void read_x_then_y()
{
	while (!x_flag.load())
		;

	if (y_flag.load())
		++ival;
}

void read_y_then_x()
{
	while (!y_flag.load())
		;

	if (x_flag.load())
		++ival;
}

void func()
{
	x_flag = false;
	y_flag = false;
	ival = 0;

	std::thread t1{ set_x };
	std::thread t2{ set_y };
	std::thread t3{ read_x_then_y};
	std::thread t4{ read_y_then_x};
	t1.join();
	t2.join();
	t3.join();
	t4.join();

	assert(ival != 0);
}

int main()
{
	for (int i = 0; i < 10000; ++i) {
		func();
	}
}

