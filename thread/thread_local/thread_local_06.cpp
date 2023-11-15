#include <syncstream>
#include <iostream>
#include <thread>

thread_local int tval{ 0 };
void func(const std::string& thread_name)
{
	++tval;
	std::osyncstream{ std::cout } << "tval in thread " << thread_name << " is " << tval << "\n";
}

int main()
{
	std::thread tx(func, "a");
	std::thread ty(func, "b");
	{
		std::osyncstream{ std::cout } << "tval in main : " << tval << '\n'; // 0
	}
	tx.join(); // 1
	ty.join(); // 1
}
