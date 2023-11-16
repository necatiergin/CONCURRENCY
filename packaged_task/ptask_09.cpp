#include <future>
#include <iostream>

int foo(int x, int y)
{
	return x * y + 5;
}

int main()
{
	std::packaged_task<double(double, double)> ptask{ [](double x, double y) { 
		return std::pow(x,y) + std::pow(y,x); }};

	std::future<double> ftr = ptask.get_future();
	ptask(3, 4);
	std::cout << ftr.get();
}
