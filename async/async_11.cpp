#include <iostream>
#include <future>

int foo(int n, char c)
{
	while (n--)
		std::cout << c;

	std::cout << '\n';

	return c;
}

int main()
{
	std::async(foo, 40, '+');
	std::async(foo, 40, '-');
	std::async(foo, 40, '*');
	std::async(foo, 40, '!');
}
