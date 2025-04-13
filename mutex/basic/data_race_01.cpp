#include <thread>
#include <mutex>
#include <iostream>

unsigned long long counter = 0;

void func()
{
	for (unsigned long long i = 0; i < 1'000'000ull; ++i) {
		++counter;
	}
}

int main()
{
	std::thread t1(func);
	std::thread t2(func);
	std::thread t3(func);
	std::thread t4(func);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	std::cout << counter << '\n';
}

/*
	Sample output: 1372864
*/
