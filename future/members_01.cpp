//future<T>::set_value

#include <future>
#include <iostream>
#include <stdexcept>

int main()
{
	std::promise<int> prom;
	//std::future<int> ftr = prom.get_future();
	//std::future ftr = prom.get_future();   // CTAD
	auto ftr = prom.get_future();

	prom.set_value(991);
	auto val = ftr.get();
	std::cout << "val = " << val << '\n';

	try {
		if (!ftr.valid()) {
			std::cout << "future object is not valid!\n";
		}
		val = ftr.get();   // future object is not valid
	}
	catch (const std::future_error& ex)
	{
		std::cout << "exception : " << ex.what() << '\n';
	}
}
