#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

class SpinLockMutex {
public:
	SpinLockMutex()
	{
		m_af.clear();
	} 

	void lock() 
	{
		while (m_af.test_and_set())
			; //NULL STATEMENT
	}

	void unlock() 
	{
		m_af.clear();
	}

 private:
	std::atomic_flag m_af; // true if thread holds mutex
};

 SpinLockMutex sm;
 unsigned long long gcount{};

 void worker() 
 {
	for (unsigned long long i = 0; i < 100'000ULL; ++i)  {
		std::scoped_lock lock(sm); 
		++gcount; 
	}

}

 int main() 
 {
	 {
		 std::jthread th1(worker);
		 std::jthread th2(worker);
	 }
	 std::cout << "gcount = " << gcount << '\n';
}
