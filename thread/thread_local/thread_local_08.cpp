#include <iostream>
#include <syncstream>
#include <mutex>

thread_local int gt{};

void func(char c)
{
	++gt;
	std::osyncstream{ std::cout } << c << " " << gt << '\n';
}

int main()
{
	using namespace std;
	vector<thread> tvec;

	for (char c = 'a'; c <= 'z'; ++c)
	{
		tvec.emplace_back(func, c);
	}
	//
	for (auto& t : tvec)
	{
		t.join();
	}
}
