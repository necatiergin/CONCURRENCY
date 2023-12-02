#include <iostream>
#include <future>

int main()
{
	using ftype = int(int, int);
	std::packaged_task<ftype> ptask;
	
	try {
		ptask(3, 6);
	}
	//catch (const std::future_error& ex) {
	catch (const std::exception& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
	}
}
