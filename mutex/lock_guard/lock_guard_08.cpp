#include <mutex>
#include <iostream>

int x{};
std::mutex mtx_func;
std::mutex mtx_foo;

void func()
{
	std::lock_guard guard{ mtx_func };
	for (int i = 0; i < 10'000; ++i)
	{
		++x;
	}
}

void foo()
{
	std::lock_guard guard{ mtx_foo };
	for (int i = 0; i < 10'000; ++i)
	{
		++x;
	}
}

int main()
{
	{
		std::jthread t1{ func };
		std::jthread t2{ foo };
	}
	std::cout << "x = " << x << '\n';
}

