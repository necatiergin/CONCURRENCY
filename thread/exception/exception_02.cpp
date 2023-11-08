#include <iostream>
#include <thread>

void foo()
{
	std::cout << "foo called!\n";
}

void func()
{
	std::cout << "func called!\n";
	throw std::runtime_error{ "runtime error exception from func\n" };
}

int main()
{
	std::thread t{ foo };

	try {
		func();
		t.join(); //if no exception thrown
	}
	catch (const std::exception& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
		t.join(); //if exception thrown
	}

	//...
}
