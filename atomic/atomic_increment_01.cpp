#include <atomic>
#include <iostream>

int main()
{
	std::atomic<int> x;

	int val = ++x; //atomic<T>::operator++()
	std::cout << "val = " << val << "\n";
	std::cout << "x = " << x << "\n";
	val = x++; //atomic<T>::operator++(int)
	std::cout << "val = " << val << "\n";
	std::cout << "x = " << x << "\n";
}
