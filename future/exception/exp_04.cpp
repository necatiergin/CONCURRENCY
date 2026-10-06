#include <future>
#include <iostream>

int main()
{
	std::future<int> ft;

	try {
		ft.get();
	}
	catch (const std::future_error& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
		std::cout << std::boolalpha << (ex.code() == std::future_errc::no_state) << '\n';
	}

}
