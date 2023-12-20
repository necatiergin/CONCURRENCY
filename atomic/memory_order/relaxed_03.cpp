#include <vector>
#include <iostream>
#include <thread>
#include <atomic>

std::atomic gcount{ 0 };

void increment()
{
	for (int i = 0; i < 10'000; ++i) 
		gcount.fetch_add(1, std::memory_order_relaxed);
}

void decrement()
{
	for (int i = 0; i < 10'000; ++i)
		gcount.fetch_sub(1, std::memory_order_relaxed);
}


int main()
{
	using namespace std;

	{
		vector<jthread> tvec;
		for (int n = 0; n < 20; ++n)
			if (n % 2)
				tvec.emplace_back(increment);
			else
				tvec.emplace_back(decrement);
	}

	cout << "gcount = " << gcount<< '\n';
}
