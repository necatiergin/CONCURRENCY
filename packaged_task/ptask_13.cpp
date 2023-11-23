#include <iostream>
#include <utility>
#include <future>
#include <thread>

int main()
{
	using ftype = int(int, int);
	std::packaged_task<ftype> pt_x; 
	std::packaged_task<ftype> pt_y([](int x, int y) 
									{return x * x + y * y; });
	pt_x = std::move(pt_y);
	std::future<int> ret = pt_x.get_future();
	std::thread(std::move(pt_x), 5, 15).detach();
	auto result = ret.get();
	std::cout << "the result is " << result << "\n";
}
