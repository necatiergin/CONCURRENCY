#include <iostream>
#include <syncstream>
#include <mutex>
#include <vector>

int gt{};		//shared variable
std::mutex mtx;   

void func(char c)
{
	std::lock_guard<std::mutex> myguard{mtx};
	++gt;
	std::osyncstream{ std::cout } << c << "   " << gt << '\n';
}

int main()
{
	using namespace std;
	vector<jthread> tvec;

	for (char c = 'a'; c <= 'z'; ++c)
	{
		tvec.emplace_back(func, c);
	}
}
