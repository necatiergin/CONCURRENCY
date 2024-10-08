#include <atomic>
#include <iostream>

int main()
{
	std::atomic<int> x{};
	x.store(98);
	std::cout << x.load() << '\n';
	std::atomic_store(&x, 30);
	std::cout << atomic_load(&x) << '\n';
	//
}
