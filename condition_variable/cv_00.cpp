/*
    In the code below, the function `func` repeatedly checks the shared
    variable `go_flag` to see whether another thread has produced a result.
    This is essentially busy-waiting and is not an efficient approach.
*/

#include <mutex>
#include <chrono>

bool go_flag{};
std::mutex mtx;

void func()
{
	std::unique_lock lock(mtx);
	while (!go_flag) {
		lock.unlock();
		std::this_thread::yield(); 
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		lock.lock();
	}
}
