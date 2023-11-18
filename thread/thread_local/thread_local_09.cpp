#include <random>
#include <iostream>
#include <syncstream>
#include <iomanip>

thread_local std::mt19937 eng{ 454255u };

void foo()
{
	std::uniform_int_distribution dist{ 10, 99 };
	auto id = std::this_thread::get_id();

	for (int i = 0; i < 10; ++i) {
		std::osyncstream{ std::cout } << id << "\t\t" << dist(eng) << '\n';
	}
}

int main()
{
	std::thread t1{ foo };
	std::thread t2{ foo };
	t1.join();
	t2.join();
}
