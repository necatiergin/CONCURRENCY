// adapted from the book "concurrency with mordern C++ by Reiner Grimm"

#include <iostream>
#include <mutex>
#include <shared_mutex>

class ILock {
public:
	virtual void lock() const = 0;
	virtual void unlock() const = 0;
};


class StrategizedLocking {
public:
	StrategizedLocking(ILock& lock) : mlock(lock)
	{
		mlock.lock();
	}

	~StrategizedLocking()
	{
		mlock.unlock();
	}
private:
	ILock& mlock;
};

struct NullObjectMutex {
	static void lock() {}
	static void unlock() {}
};

class NoLocker : public ILock {
	void lock() const override
	{
		std::cout << "NoLocker::lock()\n";
		NullObjectMutex::lock();
	}

	void unlock() const override
	{
		std::cout << "NoLocker::unlock()\n";
		NullObjectMutex::unlock();
	}
};

class ExclusiveLock : public ILock {
	void lock() const override
	{
		std::cout << " ExclusiveLock::mlock()\n";
		mtx.lock();
	}

	void unlock() const override
	{
		std::cout << " ExclusiveLock::unlock()\n";
		mtx.unlock();
	}
	mutable std::mutex mtx;
};


class SharedLock : public ILock {

	void lock() const override
	{
		std::cout << " SharedLock::lock_shared()\n";
		ms_mtx.lock_shared();
	}

	void unlock() const override
	{
		std::cout << " SharedLock::unlock_shared()\n";
		ms_mtx.unlock_shared();
	}

	mutable std::shared_mutex ms_mtx;
};


int main()
{
	NoLocker no_lock;
	StrategizedLocking st_lock1{ no_lock };
	{
		ExclusiveLock elock;
		StrategizedLocking st_lock2{ elock };
		{
			SharedLock shared_lock;
			StrategizedLocking st_lock3{ shared_lock };
		}
	}
}
