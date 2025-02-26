#include <future>
#include <iostream>

int foo(int x, int y)
{
	return x * y + 5;
}

int main()
{
	std::packaged_task<int(int, int)> ptask{ foo };
	// std::packaged_task ptask{ foo };  CTAD
	std::future<int> ftr = ptask.get_future();

	ptask(12, 45);
	std::cout << ftr.get();
}
