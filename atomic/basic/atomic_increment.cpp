#include <atomic>
#include <iostream>

int main()
{
	std::atomic<int> x;

	int i1 = ++x; 
	std::cout << "x  = " << x << '\n';
	std::cout << "i1 = " << i1 << '\n';
	int i2 = x.operator++(); 
	std::cout << "x  = " << x << '\n';
	std::cout << "i2 = " << i2 << '\n';
	std::cout << "x.load() = " << x.load() << '\n';
	int i3 = x++; 
	std::cout << "x  = " << x << '\n';
	std::cout << "i3 = " << i3 << '\n';
	int i4 = x.operator++(0); 
	std::cout << "x  = " << x << '\n';
	std::cout << "i4 = " << i4 << '\n';
}
