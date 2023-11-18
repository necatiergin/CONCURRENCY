#include <iostream>
#include <thread>
#include <atomic>

std::atomic<bool> ga_start{ false };

void func(char id)
{
	using namespace std::chrono;
	while (!ga_start)
	{
		std::this_thread::yield();
	}
	//std::this_thread::sleep_for(500ms);
	std::cout << id;
}

int main()
{
	std::thread ar_t[26];

	for (char i{ 'A' }; auto & t : ar_t)
		t = std::thread(func, i++);

	ga_start = true;

	for (auto& t : ar_t)
		t.join();
}
