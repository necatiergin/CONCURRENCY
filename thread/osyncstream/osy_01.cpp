#include <iostream>
#include <thread>
#include <syncstream>

void func()
{
	using namespace std::literals;
	std::this_thread::sleep_for(2000ms);
	std::osyncstream os{ std::cout };
	
	for (int i = 0; i < 1000; ++i)
	{
		os << 13 << " alican " << 123.43 << " mustafa\n";
	}
}

void foo()
{
	using namespace std::literals;

	std::this_thread::sleep_for(2000ms);

	for (int i = 0; i < 1000; ++i)
	{
		std::osyncstream{ std::cout } << 55 << " necati " << 35.52 << " ergin\n";
	}
}

int main()
{
	std::thread t1{ func };
	std::thread t2{ foo };
	t1.join();
	t2.join();
}
