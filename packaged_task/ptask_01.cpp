#include <future>
#include <iostream>

int main()
{
	std::packaged_task<double(double, double)> ptask([](double a, double b)
		{
			return std::pow(a, b) + std::pow(b, a);
		});

	//std::future<double> result = ptask.get_future();
	auto result = ptask.get_future();

	ptask(1.2, 3.4);

	std::cout << "result : " << result.get() << '\n';
}
