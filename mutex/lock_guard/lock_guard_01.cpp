#include <chrono>
#include <mutex>
#include <iostream>
#include <syncstream>

using namespace std;
using namespace std::literals;

std::mutex gmtx;


void func(int x)
{
	gmtx.lock();
	try {
		osyncstream{ std::cout } << this_thread::get_id() << " " << "locked the mutex\n";
		osyncstream{ std::cout } << "x = " << x << '\n';
		if (x % 2 == 0)
			throw invalid_argument{ "no even number" };
		gmtx.unlock();
		osyncstream{ std::cout } << this_thread::get_id() << " " << "unocked the mutex\n";
	}
	catch (const exception& ex) {
		osyncstream{ std::cout } << this_thread::get_id() << " exception caught : " << ex.what() << '\n';
	}
}

int main()
{
	jthread t1{ func, 4 };
	jthread t2{ func, 5 };
}
