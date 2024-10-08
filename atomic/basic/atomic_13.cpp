// volatile is not atomic

#include <atomic>
#include <iostream>
#include <thread>

//volatile int x = 0;
std::atomic x = 0;

int main()
{
	const auto fn_inc = [] {
		for (int i = 0; i < 100'000; ++i)
			++x;
		};

	const auto fn_dec = [] {
		for (int i = 0; i < 100'000; ++i)
			--x;
		};

	{
		std::jthread t1{ fn_inc };
		std::jthread t2{ fn_dec };
	}

	std::cout << "x = " << x << '\n';
}
