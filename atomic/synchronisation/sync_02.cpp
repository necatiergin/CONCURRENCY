#include <atomic>
#include <syncstream>
#include <iostream>
#include <thread>

std::atomic<int> ready_flag{ false };
int svar = 0;

void consumer()
{
	while (!ready_flag.load(std::memory_order_release)) {
		std::osyncstream{ std::cout }.put('.');
	}
	std::osyncstream{ std::cout } << '\n' << svar;
}


void producer()
{
	std::this_thread::sleep_for(std::chrono::milliseconds{ 50 });
	svar = 38764;
	ready_flag.store(true, std::memory_order_acquire);
}

int main()
{
	std::thread th_c{ consumer };
	std::thread th_p{ producer };

	th_c.join();
	th_p.join();
}
