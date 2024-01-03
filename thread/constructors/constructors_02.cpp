#include <syncstream>
#include <iostream>
#include <thread>

void foo(int x)
{
	std::osyncstream{ std::cout } << "in foo x = " << x << '\n';
}

void bar(int x, int y, int z)
{
	std::osyncstream{ std::cout} << "in bar x = " << x << '\n';
	std::osyncstream{ std::cout } << "in bar y = " << y << '\n';
	std::osyncstream{ std::cout } << "in bar z = " << z << '\n';
}

int main()
{
	std::thread tx{ foo, 1 };
	std::thread ty{ bar, 10, 20, 30 };

	tx.join();
	ty.join();
}
