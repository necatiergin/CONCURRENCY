#include <future>
#include <iostream>


void f1(void)
{
	std::future<int> fut;

	try {
		fut.get();
	}
	catch (const std::future_error& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
	}
}

void f2(void)
{
	std::future<int> fut = std::async([] { return 10; });
	fut.get();

	try {
		fut.get();
	}
	catch (const std::future_error& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
	}
}

void f3(void)
{
	auto ftr1 = std::async([] { return 10; });
	auto ftr2 = std::move(ftr1);

	try {
		ftr1.get();
	}
	catch (const std::future_error& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
	}
}

void f4(void)
{
	std::future<int> fut = std::async([] { return 10; });
	std::shared_future<int> sfut = fut.share();  
	
	try {
		fut.get();  
	}
	catch (const std::future_error& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
	}
}

int main(void)
{
	f3();
}
