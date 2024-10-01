#include <iostream>
#include <thread>
#include <syncstream>
#include <vector>

void func(int i)
{
	std::osyncstream{ std::cout } << "func runs i = " << i << '\n';
}

int main()
{
	std::vector<std::jthread> tvec;
	tvec.reserve(10);

	for (int i = 0; i < 10; ++i) {
		tvec.push_back(std::jthread{ func, i });
	}

	for (auto&& t : tvec) {
		t.join();
	}
}

