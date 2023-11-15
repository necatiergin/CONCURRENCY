#include <iostream>
#include <thread>

int main()
{
	std::thread t{ [](int x) { std::cout << x; }, 10 };	// valid

	t.join();
}
