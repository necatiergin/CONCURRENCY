#include <iostream>
#include <thread>
#include <exception>

void foo()
{
	std::cout << "foo called!\n";
}

void func()
{
	std::cout << "func called!\n";
	throw std::runtime_error{ "runtime error exception from func\n" };
}

void myterminate()
{
	std::cout << "myterminate called!\n";
	abort();
}

int main()
{
	set_terminate(myterminate);
	std::thread t{ foo };

	func();

	t.join(); //will not be executed
}
