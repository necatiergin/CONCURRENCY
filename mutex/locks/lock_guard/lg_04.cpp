#include <thread>
#include <mutex>
#include <iostream>

unsigned long long counter = 0;
std::mutex mtx;

void foo()
{
	for (unsigned long long i = 0; i < 1'000'000ull; ++i) {
		mtx.lock();
		std::lock_guard lg(mtx, std::adopt_lock);
		++counter;
	}
}

void bar()
{
	for (unsigned long long i = 0; i < 1'000'000ull; ++i) {
		std::lock_guard lg(mtx);
		++counter;
	}
}

int main()
{
	{
		std::jthread t1(foo);
		std::jthread t2(foo);
		std::jthread t3(foo);
		std::jthread t4(foo);
		std::jthread t5(bar);
		std::jthread t6(bar);
		std::jthread t7(bar);
		std::jthread t8(bar);
	}

	std::cout << "counter = " << counter << '\n';
}
