#include <exception>
#include <future>
#include <iostream>
#include <thread>
#include <utility>

struct Div {
	void operator()(std::promise<int>&& prom, int a, int b)const
	{
		try {
			if (b == 0) {
				auto err_str = "divide by zero error " + std::to_string(a) + " / " + std::to_string(b);
				throw std::runtime_error(err_str);
			}
			prom.set_value(a / b);
		}
		catch (...) {
			prom.set_exception(std::current_exception());
		}
	}
};

void func(int x, int y)
{
	std::promise<int> prom;
	std::future<int> ftr = prom.get_future();
	std::thread th(Div{}, std::move(prom), x, y);
	try {
		std::cout << x << " / " << y << " = " << ftr.get() << '\n';
	}
	catch (const std::exception& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
	}

	th.join();
}


int main()
{
	func(12, 7);
	func(12, 0);
}
