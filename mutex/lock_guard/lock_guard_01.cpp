// deadlock & exception

#include <chrono>
#include <mutex>
#include <iostream>
#include <syncstream>

std::mutex gmtx;

void func(int x)
{
	std::osyncstream ocout{ std::cout };

	gmtx.lock();
	try {
		ocout << std::this_thread::get_id() << " " << "locked the mutex\n";
		ocout << "x = " << x << '\n';
		if (x % 2 == 0)
			throw std::invalid_argument{ "no even number" };
		gmtx.unlock();
		ocout << std::this_thread::get_id() << " " << "unlocked the mutex\n";
	}
	catch (const std::exception& ex) {
		ocout << std::this_thread::get_id() << " exception caught : " << ex.what() << '\n';
	}
}

int main()
{
	std::jthread t1{ func, 4 };
	std::jthread t2{ func, 5 };
}
