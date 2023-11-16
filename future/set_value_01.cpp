#include <future>
#include <iostream>
#include <stdexcept>

int main()
{
	std::promise<int> prom;
	std::future<int> ftr = prom.get_future();
	
	prom.set_value(991);
	auto val = ftr.get();
	std::cout << "val = " << val << '\n';
	
	try {
		val = ftr.get();
	}
	catch (const std::future_error& ex)
	{
		std::cout <<"exception : " <<  ex.what() << '\n';
	}
}
