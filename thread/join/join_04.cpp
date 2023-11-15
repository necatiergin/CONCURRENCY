#include <thread>
#include <iostream>

void foo()
{
	for (int i = 0; i < 1'000'000; ++i) {
		std::cout << '*';
	}
}

void bar()
{
	for (int i = 0; i < 1'000'000; ++i) {
		std::cout << '?';
	}
}

void baz()
{
	for (int i = 0; i < 1'000'000; ++i)	{
		std::cout << '-';
	}
}

int main()
{
	using namespace std;

	thread t1{ foo };
	thread t2{ bar};
	thread t3{ baz};

	for (int i = 0; i < 1'000'000; ++i) {
		std::cout << '.';
	}

	t1.join();
	t2.join();
	t3.join();
}
