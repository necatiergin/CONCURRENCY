#include <mutex>
#include <syncstream>
#include <iostream>
#include <chrono>

std::mutex m1, m2;

using namespace std::chrono;

void foo()
{
	{
		std::scoped_lock lg(m1, m2);
		std::this_thread::sleep_for(300ms);
	}
	std::osyncstream{ std::cout } << "foo()\n";
}

void bar()
{
	{
		std::scoped_lock lg(m2, m1); 
		std::this_thread::sleep_for(300ms);
	}
	std::osyncstream{ std::cout } << "bar()\n";
}

int main()
{
	std::jthread t1{ foo };
	std::jthread t2{ bar };
	// no deadlock
}
