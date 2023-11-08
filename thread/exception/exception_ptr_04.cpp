//std::exception_ptr & std::current_exception & std::rethrow_exception

#include <iostream>
#include <stdexcept>
#include <thread>

std::exception_ptr exptr = nullptr;

void func(int x)
{
	std::cout << "func(int x) cagrildi x = " << x << '\n';
	try {
		if (x % 2 == 0)
			throw std::invalid_argument{ "gecersiz arguman" };
	}
	catch (...) {
		exptr = std::current_exception();
	}
	std::cout << "func(int x) sona erdi x = " << x << '\n';
}


int main()
{
	std::thread t{ func, 10 };
	t.join();
	try {
		if (exptr) {
			std::rethrow_exception(exptr);
		}
	}
	catch (const std::exception &ex) {
		std::cout << "exception caught : " << ex.what() << '\n';
	}
}
