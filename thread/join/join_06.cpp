#include <iostream>
#include <thread>
#include <vector>

void cprint(char c)
{
	using namespace std::literals;
	for (int i = 0; i < 1'000; ++i)
	{
		std::cout << c;
		std::this_thread::sleep_for(50ms);
	}
}

int main()
{
	std::vector<std::thread> tvec;

	for (int i = 0; i < 26; ++i) {
		tvec.push_back(std::thread{ cprint, i++ + 'A' });
	}

	for (auto& t : tvec)
	{
		t.join();
	}
}
