#include <syncstream>
#include <iostream>
#include <thread>
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
	
	//all threads joins
}

