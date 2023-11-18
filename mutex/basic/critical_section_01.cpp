#include <mutex>

std::mutex mtx;

void func()
{
	mtx.lock();

	// critical section

	mtx.unlock();
}
