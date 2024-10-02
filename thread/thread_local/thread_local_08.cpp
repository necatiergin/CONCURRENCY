#include <random>
#include <iostream>
#include <thread>

thread_local std::mt19937 eng{ 454255u };

void foo()
{
	std::uniform_int_distribution dist{ 10, 99 };

	for (int i = 0; i < 10; ++i) {
		std::cout << dist(eng) << ' ';
	}
}


int main()
{
	std::thread t1{ foo };
	t1.join();
	std::cout << '\n';
	std::thread t2{ foo };	  //same numbers are generated
	t2.join();
}
