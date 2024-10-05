#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>
#include <syncstream>

std::timed_mutex mtx;

void task(int id)
{
	using namespace std::literals;
	int cnt{};

	for (int i{}; i < 10'000; ++i) {
		
		if (mtx.try_lock_for(1us)) {
			++cnt;
			mtx.unlock();
		}

	}
	std::osyncstream{ std::cout } << id << "  " << ++cnt << '\n';
}

int main()
{
	std::vector<std::jthread> tvec;

	for (int i{}; i < 10; ++i) {
		tvec.emplace_back(task, i);
	}
}
