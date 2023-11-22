#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

std::once_flag gflag;

void func(int id)
{
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
