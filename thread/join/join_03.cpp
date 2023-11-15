#include <thread>
#include <iostream>

void func()
{
	for (int i{}; i < 1'000'000; ++i) {
		std::cout << '*';
	}
}

int main()
{
	std::thread t1{func};

	for (int i{}; i < 1'000'000; ++i) {
		std::cout << '.';
	}
	
	t1.join();
}
