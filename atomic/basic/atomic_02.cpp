#include <atomic>
#include <iostream>

int main()
{
	std::atomic x = 5;
	std::atomic y = 5;

	auto r1 = x += 2;
	auto r2 = y.fetch_add(2);

	std::cout << "r1 = " << r1 << '\n'; //7
	std::cout << "r2 = " << r2 << '\n'; //5
}
