#include <future>
#include <iostream>

int foo()
{
	return 1;
}

int main()
{
	auto ftr = std::async(foo);
	if (ftr.valid())
	{
		std::cout << "future is valid, get function can be called\n";
	}
	else
	{
		std::cout << "future is invalid, get function cannot be called\n";
	}

	auto ival = ftr.get();
	std::cout << "ival = " << ival << '\n';
	if (ftr.valid())
	{
		std::cout << "future is valid, get function can be called\n";
	}
	else
	{
		std::cout << "future is invalid, get function cannot be called\n";
	}
	
	try {
		auto i = ftr.get();
	}
	catch (const std::future_error& ex)
	{
		std::cout << "exception caught : " << ex.what() << '\n';
	}
}
