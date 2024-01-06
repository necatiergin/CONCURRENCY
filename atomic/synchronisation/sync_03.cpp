#include <atomic>
#include <syncstream>
#include <iostream>
#include <thread>

std::atomic<int> ready_flag{ false };
int svar = 0;

void consumer()
{
	while (!ready_flag) {
		std::osyncstream{ std::cout }.put('.');
	}
	std::osyncstream{ std::cout } << '\n' << svar;
}


void producer()
{
	std::this_thread::sleep_for(std::chrono::milliseconds{ 200 });
	svar = 38764;
	ready_flag = true;
}

int main()
{
	std::jthread th_c{ consumer };
	std::jthread th_p{ producer };
}
