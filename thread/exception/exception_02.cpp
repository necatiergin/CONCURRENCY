#include <thread>
#include <syncstream>
#include <iostream>

void func(int x, char c)
{
	std::osyncstream ocout{ std::cout };
	
	ocout << "func(int x) x = " << x << '\n';

	try {
		if (x % 2 == 0)
			throw std::runtime_error("even number error!");
	}
	catch (const std::exception& ex) {
		ocout << "\nexception caught: " << ex.what() << '\n';
	}
	std::this_thread::sleep_for(std::chrono::duration<double>{2.});
	for (int i = 0; i < x; ++i) {
		ocout.put(c);
	}
}

int main()
{
	std::thread t1(func, 10000, '*');
	std::thread t2(func, 14000, '.');

	t1.join();
	t2.join();
}
