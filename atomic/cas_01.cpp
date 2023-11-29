#include <iostream>
#include <utility>
#include <atomic>


int main()
{
	std::atomic<int> x;
	x.store(5);

	//int expected{ 5 };
	int expected{ 7 };
	int desired{ 95 };
	auto b = x.compare_exchange_strong(expected, desired);
	std::cout << std::boolalpha;

	std::cout << "b = " << b << "\n";
	std::cout << "x = " << x << "\n";
	std::cout << "expected = " << expected << "\n";
	std::cout << "desired  = " << desired << "\n";	
}
