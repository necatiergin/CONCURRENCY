#include <chrono>
#include <mutex>
#include <iostream>

using namespace std::literals;

std::mutex gmtx;

void func(int n, char c)
{
	
	for (int i = 0; i < n; ++i) {
		try {
			//gmtx.lock();
			std::lock_guard lg{ gmtx };
			std::cout << c;
			if ((n + 1) % 7 == 0)
				throw std::runtime_error{ "error in loop!\n" };
			std::this_thread::sleep_for(50ms);
			//gmtx.unlock();
		}
		catch (const std::exception& ex) {
			//std::cout << "exception caught: " << ex.what() << '\n';
		}
	}
	std::cout << '\n';

}

int main()
{
	std::thread t1{ func, 20, 'A'};
	std::thread t2{ func, 20, 'B'};
	std::thread t3{ func, 20, 'C'};

	t1.join();
	t2.join();
	t3.join();
}
