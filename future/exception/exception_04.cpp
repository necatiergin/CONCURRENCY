#include <iostream>
#include <future>

/*
	from cppreference.com
	The implementations are encouraged to detect the case when valid == false before the call 
	and throw a std::future_error with an error condition of std::future_errc::no_state.
*/

int main()
{
	std::promise<int> prom;
	auto ftr = prom.get_future();
	prom.set_value(10);
	std::cout << ftr.get() << '\n';
	
	try {
		ftr.wait();
	}
	catch (const std::exception& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
	}
}
