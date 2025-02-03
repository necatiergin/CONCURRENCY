#include <syncstream>
#include <iostream>
#include <thread>

void foo(int x)
{
	std::osyncstream{ std::cout } << "in foo x = " << x << '\n';
}

void bar(int x, int y, int z)
{
	std::osyncstream osout{ std::cout };
	osout << "in bar x = " << x << '\n';
	osout << "in bar y = " << y << '\n';
	osout << "in bar z = " << z << '\n';
}

int main()
{
	std::thread tx{ foo, 1 };
	std::thread ty{ bar, 10, 20, 30 };

	tx.join();
	ty.join();
}
