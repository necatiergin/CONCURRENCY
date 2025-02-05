#include <syncstream>
#include <iostream>
#include <thread>
#include <vector>

thread_local int gt{};

void func(char c)
{
	++gt;
	std::osyncstream{ std::cout } << c << ' ' << gt << '\n';
}

int main()
{
	std::vector<std::jthread> tvec;

	for (char c = 'a'; c <= 'z'; ++c)
	{
		tvec.emplace_back(func, c);
	}
}
