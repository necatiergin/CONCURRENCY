#include <iostream>
#include <future>
#include <thread>
#include <chrono>

using namespace std::literals;

void func(std::promise<int> iprom) 
{
	std::this_thread::sleep_for(5s);
	iprom.set_value(20);
}

int main() 
{
	std::promise<int> prom;
	auto ft = prom.get_future();
	std::thread th(func, std::move(prom));

	std::future_status status{};
	do {
		status = ft.wait_for(200ms);
		std::cout << "... doing some work here\n" << std::flush;
	} while (status != std::future_status::ready);

	std::cout << "the return value is " << ft.get() << '\n';

	th.join();
}
