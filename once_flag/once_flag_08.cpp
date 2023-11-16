#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

std::once_flag gflag;
using namespace std::literals;

void foo()
{
	std::this_thread::sleep_for(100ms);
	std::call_once(gflag, []() {					// DİKKAT! Aynı Once flag değişkeni
		std::cout << "registered in foo\n"; });
	///...
}

void bar()
{
	std::this_thread::sleep_for(100ms);
	std::call_once(gflag, []() {					// DİKKAT! Aynı Once flag değişkeni
		std::cout << "registered in bar\n"; });
	///...
}

int main()
{
	std::thread a[10];
	for (int i = 0; i < 10; ++i)
	{
		a[i] = i % 2 == 0 ? std::thread{ bar } : std::thread{ foo };
	}
	for (auto& th : a)
		th.join();
}
