#include <iostream>
#include <syncstream>

struct Myclass {
	Myclass(int x)
	{
		std::osyncstream{ std::cout } << "Myclass ctor x = " << x << " this = " << this << '\n';
	}
	~Myclass()
	{
		std::osyncstream{ std::cout } << "Myclass destructor this = " << this << '\n';
	}
};


void foo(int x)
{
	thread_local Myclass m(x);
}


void func(int x)
{
	std::osyncstream{ std::cout } << "func(int) called x = " << x << '\n';
	foo(x);
}

int main()
{

	{
		std::jthread t1{ func, 1 };
		std::jthread t2{ func, 2 };
		std::jthread t3{ func, 3 };
		std::jthread t4{ func, 4 };
	}

	std::cout << "main is still running...\n";
}
