#include <future>
#include <iostream>
#include <syncstream>


struct SumSquare {
	void operator()(std::promise<int>&& prom, int a, int b)const
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
	std::future<int> ftr = prom.get_future();
	std::cout << "ftr is " << (ftr.valid() ? "valid" : "invalid") << '\n'; //valid

	std::jthread th(SumSquare{}, std::move(prom), 5, 9);
	std::cout << "ftr is " << (ftr.valid() ? "valid" : "invalid") << '\n'; //valid

	std::shared_future<int> s_ftr = ftr.share();
	std::cout << "ftr is " << (ftr.valid() ? "valid" : "invalid") << '\n'; // invalid
	
	(void)getchar();

	std::jthread t1(func, s_ftr);
	std::jthread t2(func, s_ftr);
	std::jthread t3(func, s_ftr);
	std::jthread t4(func, s_ftr);
	std::jthread t5(func, s_ftr);
}
