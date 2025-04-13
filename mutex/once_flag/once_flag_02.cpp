#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

std::once_flag gflag;

void func(int id)
{
	std::this_thread::sleep_for(std::chrono::milliseconds{ 500 });
	std::call_once(gflag, [id]() {
		// This function will be invoked only once.
		std::cout << "first: " << id << '\n';
		});
}

int main()
{
	std::vector<std::jthread> tvec;
	tvec.reserve(16);

	for (int i{}; i < 12; ++i) {
		tvec.emplace_back(func, i);
	}
}
