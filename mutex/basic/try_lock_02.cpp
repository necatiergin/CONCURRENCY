// std::mutex::try_lock

#include <iostream>
#include <thread>
#include <mutex>

int counter{};
std::mutex counter_mtx;

void try_increase()
{
	for (int i = 0; i < 100'000; ++i) {
		if (counter_mtx.try_lock()) {
			++counter;
			counter_mtx.unlock();
		}
	}
}

int main()
{
	{
		std::jthread ar_t[10];
		for (int i = 0; i < 10; ++i)
			ar_t[i] = std::jthread(try_increase);
	}

	std::cout << counter << " times incremented.\n";
}

/*
	Sample output: 78718 times incremented
*/
