#include <thread>
#include <iostream>

int main()
{
	boolalpha(std::cout);

	std::thread tx;

	std::cout << (tx.get_id() == std::thread::id{}) << '\n';
	tx = std::thread{ []() {} };
	std::cout << (tx.get_id() == std::thread::id{}) << '\n';
	tx.join();
	std::cout << (tx.get_id() == std::thread::id{}) << '\n';
}
