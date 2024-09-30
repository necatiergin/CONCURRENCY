#include <future>
#include <iostream>
#include <thread>
#include <utility>
#include <syncstream>

struct SumSquare {
	void operator()(std::promise<int>&& prom, int a, int b)
	{
		prom.set_value(a * a + b * b);
	}
};

void func(std::shared_future<int> sftr)
{
	std::osyncstream os{ std::cout };
	os << "threadId (" << std::this_thread::get_id() << "): ";
	os << "result = " << sftr.get() << '\n';
}

int main()
{
	std::promise<int> prom;
	std::shared_future sftr = prom.get_future();

	std::jthread th(SumSquare{}, std::move(prom), 5, 9);

	std::jthread t1(func, sftr);
	std::jthread t2(func, sftr);
	std::jthread t3(func, sftr);
	std::jthread t4(func, sftr);
	std::jthread t5(func, sftr);
}
