#include <iostream>
#include <cmath>
#include <thread>
#include <future>

double sum_square(double x, double y) 
{
	return x * x + y * y;
}

int main() 
{
	std::packaged_task<double(double, double)> task(sum_square);
	task(1.5, 3.2);
	std::cout << task.get_future().get() << '\n';
	task.reset();
	auto ftr = task.get_future();
	std::jthread th(std::move(task), 4.3, 2.6);
	th.detach();
	std::cout << ftr.get() << '\n';
}
