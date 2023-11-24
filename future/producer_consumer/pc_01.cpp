#include <future>
#include <thread>
#include <iostream>
#include <utility>

double func_compute(double dval)
{
	//...
	return dval * dval;
}

void produce(std::promise<double> prms, double dval)
{
	prms.set_value(func_compute(dval));
}

int main()
{
	std::promise<double> prms;
	auto ftr = prms.get_future();
	//we launch the produce thread
	std::jthread producer(produce, std::move(prms), 4.5);
	std::cout << ftr.get() << '\n';
}
