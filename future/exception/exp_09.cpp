#include <future>
#include <iostream>

int main()
{
	std::promise<int> prom;
	auto ft1 = prom.get_future();

	prom.set_value(12);
	try {
		prom.set_value(12);
	}
	catch (const std::future_error& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
		std::cout << std::boolalpha << (ex.code() == std::future_errc::promise_already_satisfied) << '\n';
	}
}
