#include <mutex>

std::mutex mtx;

void f1()
{
	//std::unique_lock<std::mutex> lock(mtx);
	std::unique_lock lock(mtx);
}

void f2()
{
	mtx.lock();
	std::unique_lock lock(mtx, std::adopt_lock);
}

void f3()
{
	std::unique_lock ulock(mtx, std::defer_lock);

	ulock.lock();
}

void f4()
{
	std::unique_lock ulock(mtx, std::try_to_lock);
	if (ulock.owns_lock()) {
		//...
	}
}
