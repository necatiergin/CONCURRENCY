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
		os << "threadId(" << std::this_thread::get_id() << "): ";
		os << "result = " << sftr.get() << std::endl;
}

int main() 
{
	std::promise<int> prom;
	std::shared_future<int> sftr = prom.get_future();

	std::thread th(SumSquare{}, std::move(prom), 5, 9);
	
	std::thread t1(func, sftr);
	std::thread t2(func, sftr);
	std::thread t3(func, sftr);
	std::thread t4(func, sftr);
	std::thread t5(func, sftr);
	
	th.join();
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
}
