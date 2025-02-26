#include <utility>
#include <future>
#include <iostream>
#include <thread>
#include <deque>

class Summer {
public:
	auto operator()(int from, int to) const
	{
		int sum{};
		for (int i = from; i < to; ++i)
			sum += i;
		return sum;
	}
};


int main() 
{
	Summer sum1;
	Summer sum2;
	Summer sum3;
	Summer sum4;

	using ftype = int(int, int);
	std::packaged_task<ftype> pt1(sum1);
	std::packaged_task<ftype> pt2(sum2);
	std::packaged_task<ftype> pt3(sum3);
	std::packaged_task<ftype> pt4(sum4);
	
	auto ft1 = pt1.get_future();
	auto ft2 = pt2.get_future();
	auto ft3 = pt3.get_future();
	auto ft4 = pt4.get_future();

	std::deque<std::packaged_task<int(int, int)>> td;
	td.push_back(std::move(pt1));
	td.push_back(std::move(pt2));
	td.push_back(std::move(pt3));
	td.push_back(std::move(pt4));
	
	int begin{ 1 };
	int increment{ 2500 };
	int end = begin + increment;
	
	while (!td.empty()) {
		auto task = std::move(td.front());
		td.pop_front();
		std::thread t(std::move(task), begin, end);
		begin = end;
		end += increment;
		t.detach();
	}
	
	 auto sum = ft1.get() + ft2.get() +	ft3.get() + ft4.get();
	
	 std::cout << "result = " << sum << '\n';
}
