#include <iostream>
#include <thread>

//thread class constructor may take any callable

int main()
{
	auto fn{ [] { std::cout << "hello\n"; } };
	std::thread t{ fn };
	t.join();
}
