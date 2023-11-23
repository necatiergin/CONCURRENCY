#include <exception>
#include <future>
#include <iostream>
#include <thread>
#include <utility>
#include <string>

//struct Div {
//	void operator()(std::promise<int>&& prom, int a, int b)const
//	{
//		try {
//			if (b == 0) {
//				auto err_str = "divide by zero error " + std::to_string(a) + " / " + std::to_string(b);
//				throw std::runtime_error(err_str);
//			}
//			prom.set_value(a / b);
//		}
//		catch (...) {
//			prom.set_exception(std::current_exception());
//		}
//	}
//};

struct Div {
	void operator()(std::promise<int>&& prom, int a, int b)const
	{
		if (b == 0) {
			auto err_str = "divide by zero error " + std::to_string(a) + " / " + std::to_string(b);
			prom.set_exception(std::make_exception_ptr(std::runtime_error(err_str)));
			return;
		}
		prom.set_value(a / b);
	}
};

void func(int x, int y)
{
	std::promise<int> prom;
	auto ftr = prom.get_future();
	std::jthread th(Div{}, std::move(prom), x, y);
	try {
		std::cout << x << " / " << y << " = " << ftr.get() << '\n';
	}
	catch (const std::exception& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
	}
}

int main()
{
	func(12, 7);
	func(12, 0);
}

/*
template <class E>
std::exception_ptr make_exception_ptr( E e ) noexcept;

Creates an std::exception_ptr that holds a reference to a copy of e. 
This is done as if executing the following code:

try {
    throw e;
} catch(...) {
    return std::current_exception();
}

*/
