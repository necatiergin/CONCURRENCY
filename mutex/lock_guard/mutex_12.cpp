#include <iostream>
#include <syncstream>
#include <mutex>

int gt{};
std::mutex m;

void func(char c)
{
	std::lock_guard<std::mutex> myguard{ m };
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
