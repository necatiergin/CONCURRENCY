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
		//x += 2;		//4
		x.fetch_add(2); //5
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
