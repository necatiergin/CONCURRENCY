#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

std::once_flag gflag;

void func(int id)
{
	using namespace std::literals;
	std::this_thread::sleep_for(500ms);
	std::call_once(gflag, [id]() {
		std::cout << id << " threadi icin cagrildi\n"; });
	///...
}

int main()
{
	std::vector<std::thread> tvec;
  
	for (int i = 0; i < 10; ++i)
	{
		tvec.emplace_back(func, i);
	}
  
	for (auto& th : tvec)
		th.join();
}
