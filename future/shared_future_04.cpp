#include <iostream>
#include <future>
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

	std::thread th(SumSquare{}, std::move(prom), 5, 9);
	std::cout << "ftr is " << (ftr.valid() ? "valid" : "invalid") << '\n'; //valid
	
	std::shared_future<int> s_ftr = ftr.share();
	std::cout << "ftr is " << (ftr.valid() ? "valid" : "invalid") << '\n'; // invalid
	(void)getchar();
	
	std::thread t1(func, s_ftr);
	std::thread t2(func, s_ftr);
	std::thread t3(func, s_ftr);
	std::thread t4(func, s_ftr);
	std::thread t5(func, s_ftr);
	
	th.join();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
}

Output
------
ftr is valid
ftr is valid
ftr is invalid

threadId(3764) : result = 106
threadId(12660) : result = 106
threadId(8256) : result = 106
threadId(1352) : result = 106
threadId(22156) : result = 106
