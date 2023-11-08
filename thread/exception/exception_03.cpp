#include <iostream>
#include <thread>

void func()
{
	std::cout << "func is called\n";
	throw std::runtime_error{ "error from func\n" }; //terminate is called if func is called not from main thread
}

int main()
{
	try {
		std::thread t{ func };
	}
	catch (const std::exception& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
	}
}
