#include <thread>
#include <iostream>

using namespace std::chrono_literals;

void put_dots()
{
	for (int i = 0; i < 100; ++i) {
		std::this_thread::sleep_for(50ms);
		std::cout.put('.');
	}
}

void put_stars()
{
	for (int i = 0; i < 100; ++i) {
		std::this_thread::sleep_for(50ms);
		std::cout.put('*');
	}
}

int main()
{
	std::jthread jt1{ put_dots };
	std::jthread jt2{ put_stars};
}
