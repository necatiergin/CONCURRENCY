#include <future>
#include <iostream>

int foo()
{
	return 1;
}

int main()
{
	const char* const pvalid = "future is valid, get function can be called\n";
	const char* const pinvalid = "future is invalid, get function cannot be called\n";

	auto ftr = std::async(foo);
	std::cout << (ftr.valid() ? pvalid : pinvalid);
	auto ival = ftr.get();
	std::cout << "ival = " << ival << '\n';
	std::cout << (ftr.valid() ? pvalid : pinvalid);

	try {
		auto i = ftr.get();
	}
	catch (const std::future_error& ex)
	{
		std::cout << "exception caught : " << ex.what() << '\n';
	}
}
