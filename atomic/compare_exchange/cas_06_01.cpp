#include <atomic>
#include <iostream>
#include <vector>
#include <thread>

std::atomic<unsigned> a = 1;

void foo()
{
	unsigned old_value = a.load();

	while (!a.compare_exchange_strong(old_value, old_value * 2))
		;
}

int main()
{
	{
		std::vector<std::jthread> tvec;

		for (int i = 0; i < 31; ++i) {
			tvec.emplace_back(foo);
		}
	}

	std::cout << "a = " << a << '\n';
}

