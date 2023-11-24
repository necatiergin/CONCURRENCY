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
	std::jthread t1(foo);
	std::jthread t2(foo);
	t1.join();
	t2.join();
	std::cout << g_count << '\n';
}
