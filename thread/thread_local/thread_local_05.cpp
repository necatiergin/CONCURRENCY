#include <iostream>
#include <syncstream>

struct Myclass {
	Myclass(int x)
	{ 
		std::osyncstream{ std::cout } << "Myclass ctor x = " << x << " this = " << this << std::endl;
	}
};


void foo(int x)
{
	thread_local Myclass m(x);
}


void func(int x)
{
	std::osyncstream{ std::cout } << "func(int) cagrildi x = " << x << "\n";
	foo(x);
}

int main()
{

	std::thread t1{ func, 1 };
	std::thread t2{ func, 2 };
	std::thread t3{ func, 3 };
	std::thread t4{ func, 4 };

	t1.join();
	t2.join();
	t3.join();
	t4.join();
}
