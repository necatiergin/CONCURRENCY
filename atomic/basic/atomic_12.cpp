#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic<int> x{ 0 };

void foo()
{
	for (int i = 0; i < 10000; ++i) {
		// ++x;			//1
		// x++;			//2
		//x = x + 1;    //3
		//x += 1;		//4
		//x.fetch_add(1); //5
		//x.exchange(x + 1); // 6
		int expected = x; while (!x.compare_exchange_weak(expected, x + 1)); // 7
	}
}

int main()
{
	using namespace std;

	{
		vector<jthread> tvec;

		for (int i = 0; i < 20; ++i)
			tvec.emplace_back(foo);
	}

	cout << "x = " << x << '\n';
}
