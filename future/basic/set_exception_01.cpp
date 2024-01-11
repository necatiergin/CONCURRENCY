#include <future>
#include <iostream>
#include <thread>
#include <stdexcept>

void foo(std::promise<int>&&prom, int x)
{
	if (x % 2 == 0)
		prom.set_exception(std::make_exception_ptr(std::runtime_error{ "even number error!" }));
	else
		prom.set_value(x * x - 4);
}

int main()
{
	std::promise<int> prom;
	auto ft = prom.get_future();
	

	std::jthread tx{ foo, std::move(prom), 30 };
	try {
		std::cout << ft.get() << '\n';
	}
	catch (const std::exception& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
	}
}
