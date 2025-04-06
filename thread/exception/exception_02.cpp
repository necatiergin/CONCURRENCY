#include <thread>
#include <syncstream>
#include <iostream>

void func(int x, char c)
{
	std::osyncstream { std::cout } << "func(int x) x = " << x << '\n';

	try {
		if (x % 2 == 0)
			throw std::runtime_error("even number error!");
	}
	catch (const std::exception& ex) {
		std::osyncstream{ std::cout } << "\nexception caught: " << ex.what() << '\n';
	}
	std::this_thread::sleep_for(std::chrono::duration<double>{2.});
	for (int i = 0; i < x; ++i) {
		std::osyncstream{ std::cout }.put(c);
	}
}

int main()
{
	std::thread t1(func, 100, '*');
	std::thread t2(func, 140, '.');

	t1.join();
	t2.join();
}
