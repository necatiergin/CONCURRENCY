std::mutex mtx;

void func()
{
	mtx.lock();
	std::unique_lock<std::mutex> lock(mtx, std::adopt_lock);
}

void func()
{
	std::unique_lock<std::mutex> ulock(mtx, std::defer_lock);

	ulock.lock();
}

void func()
{
	std::unique_lock<std::mutex> ulock(mtx, std::try_to_lock);
}
