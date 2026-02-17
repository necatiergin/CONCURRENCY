#include <iostream>
#include <future>
#include <thread>

int main()
{
	using ftype = int(int, int);
	std::packaged_task<ftype> pt_x;
	std::packaged_task<ftype> pt_y([](int x, int y) {return x * x + y * y; });

	// pt_x = pt_y; // error

	pt_x = std::move(pt_y);
	std::future<int> ftr = pt_x.get_future();
	std::thread{ std::move(pt_x),4,6 }.detach();
	std::cout << ftr.get();
}
