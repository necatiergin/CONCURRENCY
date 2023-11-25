#include <thread>
#include <mutex>
#include <iostream>

unsigned long long counter = 0;
std::mutex mtx;

void func()
{
	for (unsigned long long i = 0; i < 1'000'000ull; ++i) {
		mtx.lock();
		std::lock_guard<std::mutex> lg(mtx, std::adopt_lock);
		++counter;
	}
}
int main()
{
	{
		std::jthread t1(func);
		std::jthread t2(func);
		std::jthread t3(func);
		std::jthread t4(func);
	}
	
	std::cout << "counter = " << counter << '\n';
}

