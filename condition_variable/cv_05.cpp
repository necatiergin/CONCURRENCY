#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <string>
#include <syncstream>

std::condition_variable cv;
std::mutex mtx;
int gval = 0;

using namespace std::literals;

void waits(const std::string& id)
{
	std::unique_lock<std::mutex> lk(mtx);
	std::osyncstream{ std::cout } << id << " is waiting\n";
	cv.wait(lk, [] {return gval == 1; });

	std::osyncstream{ std::cout } << id << " finished waiting. gval == 1\n";
}

void signals(const std::string& id)
{
	std::this_thread::sleep_for(1s);

	std::osyncstream{ std::cout } << id << " notifying\n";
	
	cv.notify_all();
	std::this_thread::sleep_for(std::chrono::seconds(1s));
	{
		std::lock_guard<std::mutex> lk(mtx);
		gval = 1;
		std::osyncstream{ std::cout } << id << " notifying again\n";
	}
	cv.notify_all();
}

int main()
{
	std::jthread 
	t1(waits, "t1"), 
	t2(waits, "t2"), 
	t3(waits, "t3"), 
	t4(signals, "t4"), 
	t5(signals, "t5");
}
