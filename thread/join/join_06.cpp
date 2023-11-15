#include <iostream>
#include <thread>
#include <syncstream>

void cprint(char c)
{
	using namespace std::literals;
	for (int i = 0; i < 1000; ++i)
	{
		std::cout << c;
		std::this_thread::sleep_for(50ms);
	}
}

int main()
{
	std::vector<std::thread> ta;
	
	for (int i{}; auto & t : ta)
	{
		ta.push_back(std::thread{ cprint,i + 'A' });
	}

	for (auto& t : ta)
	{
		t.join();
	}
}
