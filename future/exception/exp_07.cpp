#include <future>
#include <iostream>

int main()
{
	std::promise<int> prom_x;
	auto ft = prom_x.get_future();
	auto prom_y = std::move(prom_x);

	try {
		//auto ftr = prom_x.get_future();
		//prom_x.set_value(123);
		prom_x.set_exception(make_exception_ptr(std::runtime_error("error")));
	}
	catch (const std::future_error& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
		std::cout << std::boolalpha << (ex.code() == std::future_errc::no_state) << '\n';
	}
}
