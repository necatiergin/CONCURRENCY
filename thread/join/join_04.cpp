#include <thread>
#include <iostream>

void foo()
{
	for (int i{}; i < 10'000; ++i) {
		std::cout << '*';
	}
}

void bar()
{
	for (int i{}; i < 10'000; ++i) {
		std::cout << '?';
	}
}

void baz()
{
	for (int i{}; i < 10'000; ++i) {
		std::cout << '-';
	}
}

int main()
{
	std::thread t1{ foo };
	std::thread t2{ bar };
	std::thread t3{ baz };

	for (int i = 0; i < 10'000; ++i) {
		std::cout << '.';
	}

	t1.join();
	t2.join();
	t3.join();
}
