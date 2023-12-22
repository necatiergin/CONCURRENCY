// adapted from the book "concurrency with mordern C++ by Reiner Grimm"

#include <iostream>
#include <mutex>
#include <shared_mutex>


template <typename LOCK>
class StrategizedLocking {
public:
	StrategizedLocking(LOCK & l) : mlock(l) 
	{
		mlock.lock();
	}

	~StrategizedLocking() 
	{
		mlock.unlock();
	}
private:
	LOCK& mlock;
};


struct NullObjectMutex {
	static void lock() {}
	static void unlock() {}
};

class NoLocker {
public:
	void lock() const 
	{
		std::cout << "NoLocker::lock()\n";
		NullObjectMutex::lock();
	}

	void unlock() const 
	{
		std::cout << "NoLocker::unlock()\n";
		NullObjectMutex::unlock();
	}
};



class ExclusiveLock {
public:
	void lock() const
	{
		std::cout << " ExclusiveLock::lock()\n";
		mtx.lock();
	}

	void unlock() const 
	{
		std::cout << " ExclusiveLock::unlock()\n";
		mtx.unlock();
	}
	mutable std::mutex mtx;
};

class SharedLock {
public:
	void lock() const
	{
		std::cout << " SharedLock::lock_shared()\n";
		shared_mtx.lock_shared();
	}

	void unlock() const 
	{
		std::cout << " SharedLock::unlock_shared()\n";
		shared_mtx.unlock_shared();
	}
	mutable std::shared_mutex shared_mtx;
};


int main() 
{
	NoLocker no_lock;
	StrategizedLocking<NoLocker> st_lock1{ no_lock };
	{
		ExclusiveLock elock;
		StrategizedLocking<ExclusiveLock> st_lock2{ elock };
		{
			SharedLock shared_lock;
			StrategizedLocking<SharedLock> st_lock3{ shared_lock };
		}
	}
}
