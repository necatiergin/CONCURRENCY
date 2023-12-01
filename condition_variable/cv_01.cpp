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
