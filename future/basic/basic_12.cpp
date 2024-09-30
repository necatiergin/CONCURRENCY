#include <future>
#include <iostream>

//we can call get fucntion of the future object only once

int main()
{
	std::promise<int> prom;
	auto ft = prom.get_future();

	prom.set_value(10);
	auto val = ft.get();
	std::cout << "val = " << val << '\n';

	try {
		auto x = ft.get();
	}
	catch (const std::future_error& ex)
	{
		std::cout << "exception caught : " << ex.what() << '\n';
	}
}
