#include <syncstream>
#include <iostream>

void foo()
{
	std::osyncstream{ std::cout } << std::this_thread::get_id() << '\n';
}

int main()
{
	std::thread tx{ foo };
	std::osyncstream{ std::cout } << tx.get_id() << '\n';
	tx.join();
}
