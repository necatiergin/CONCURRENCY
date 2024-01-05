#include <iostream>
#include <thread>

void func()
{
	std::cout << "func is called\n";
	throw std::runtime_error{ "error from func\n" }; 
	//terminates
}

void myterminate()
{
	std::cout << "myterminate called!\n";
	abort();
}

int main()
{
	set_terminate(myterminate);
	try {
		std::thread t{ func };
	}
	catch (const std::exception& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
	}
}
