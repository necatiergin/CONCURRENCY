#include <iostream>
#include <thread>
#include <chrono>

void print_block(int n, char c)
{
	using namespace std::literals;

	for (int i = 0; i < n; ++i) {
		std::this_thread::sleep_for(5ms);
		std::cout << c;
	}
	std::cout << '\n';
}

int main()
{
	std::thread th1(print_block, 50, '*');
	std::thread th2(print_block, 50, '$');
	std::thread th3(print_block, 50, '+');
	std::thread th4(print_block, 50, '!');
	th1.join();
	th2.join();
	th3.join();
	th4.join();
}

