#include <atomic>
#include <iostream>
#include <thread>

int main()
{
	//int x = 0;
	std::atomic x = 0;

	auto f = [&x] {
		for (int i = 0; i < 10000; ++i)
			++x;
		};
	
	{
		std::jthread t1{ f };
		std::jthread t2{ f };
		std::jthread t3{ f };
	}

	std::cout << "x = " << x << '\n';
}
