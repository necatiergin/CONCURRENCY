#include <future>
#include <iostream>

int main()
{
	std::promise<int> p;
	auto f = p.get_future();

	p.set_value(10);

	std::cout << f.get() << '\n';
	
	try {
		f.get();  // no associated shared state
	}
	catch (const std::future_error& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
		std::cout << std::boolalpha << (ex.code() == std::future_errc::no_state) << '\n';
	}
}
