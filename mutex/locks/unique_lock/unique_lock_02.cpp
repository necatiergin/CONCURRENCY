#include <mutex>
#include <iostream>

std::timed_mutex mtx;

void func()
{
	using namespace std::literals;
	//std::unique_lock<std::timed_mutex> ulock(mtx, 500ms);
	
	std::unique_lock ulock(mtx, 500ms);
	//...
}
