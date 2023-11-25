#include <iostream>
#include <thread>
#include <mutex>

unsigned long long g_count{};
std::mutex mtx;

void foo()
{
	for (unsigned long long i{}; i < 1'000'000; ++i) {
		std::scoped_lock lock(mtx);
		++g_count;
	}
}

int main()
{
	{
		std::jthread t1(foo);
		std::jthread t2(foo);
	}
	std::cout << g_count << '\n';
}
