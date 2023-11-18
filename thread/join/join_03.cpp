#include <thread>
#include <iostream>

void func()
{
	for (int i{}; i < 10'000; ++i) {
		std::cout << '*';
	}
}

int main()
{
	std::thread t{func};

	for (int i{}; i < 10'000; ++i) {
		std::cout << '.';
	}
	
	t.join();
}
