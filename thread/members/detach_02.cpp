#include <iostream>
#include <vector>
#include <thread>
#include <numeric>

void fworker(const std::vector<int>* vp)
{
	std::cout << std::accumulate(vp->begin(), vp->end(), 0) << '\n';
}


void thread_starter()
{
	std::vector<int> ivec(1'000'000, 5);
	std::thread t{ fworker, &ivec }; //local object with automatic storage
	t.detach();
}

int main()
{
	thread_starter();
	std::this_thread::sleep_for(std::chrono::seconds{ 5 });
}
