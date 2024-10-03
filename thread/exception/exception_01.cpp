#include <thread>
#include <stdexcept>
#include <iostream>

void f(int x)
{
	if (x == 0)
		throw std::invalid_argument{ "zero value error!" };
}


int main()
{
	try {
		std::thread t{ f, 0 }; //std::terminate is called
		t.join();
	}
	catch (const std::exception& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
	}
}
