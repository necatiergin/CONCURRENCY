#include<mutex>
#include <iostream>
#include <syncstream>

std::mutex a_mtx;
std::mutex b_mtx;

void foo()
{
	using namespace std::literals;
	std::lock(a_mtx, b_mtx);
	std::lock_guard guard1{ a_mtx, std::adopt_lock };
	std::lock_guard guard2{ b_mtx, std::adopt_lock };
	std::this_thread::sleep_for(100ms);
	std::osyncstream{ std::cout } << "foo ends" << '\n';
}

void bar()
{
	using namespace std::literals;
	std::lock(a_mtx, b_mtx);
	std::lock_guard guard1{ a_mtx, std::adopt_lock };
	std::lock_guard guard2{ b_mtx, std::adopt_lock };
	std::this_thread::sleep_for(100ms);
	std::osyncstream{ std::cout } << "bar ends" << '\n';
}

int main()
{
	std::jthread t1{ foo };
	std::jthread t2{ bar };
}
