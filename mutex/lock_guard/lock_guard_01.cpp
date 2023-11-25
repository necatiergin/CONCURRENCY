#include <chrono>
#include <mutex>
#include <iostream>
#include <syncstream>

using namespace std::literals;

std::mutex gmtx;

void func(int n, char c)
{
	for (int i = 0; i < n; ++i) {
		try {
			//gmtx.lock();
			std::lock_guard lg{ gmtx };
			std::osyncstream{ std::cout } << c << '\n';
			if (i % 3 == 0)
				throw std::runtime_error{ "error in loop!\n" };
			std::this_thread::sleep_for(50ms);
			//gmtx.unlock();
		}
		catch (const std::exception& ex) {
			std::osyncstream{ std::cout } << "\nexception caught: " << ex.what() << '\n';
		}
	}
	std::cout << '\n';

}

int main()
{
	std::jthread t1{ func, 3, 'A' };
	std::jthread t2{ func, 3, 'B' };
	std::jthread t3{ func, 3, 'C' };
}
