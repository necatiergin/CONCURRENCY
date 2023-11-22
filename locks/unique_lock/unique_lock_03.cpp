#include <iostream>
#include <thread>
#include <mutex>

unsigned long gcount{};
std::mutex mtx;

void foo() 
{
	for (unsigned long i{}; i < 1'000'000ul; ++i) {
		std::unique_lock lock(mtx, std::defer_lock);
		lock.lock(); //mutex'i ediniyor.
		++gcount;
		lock.unlock(); // mutex'i serbest bırakıyor.
		// ...
		lock.lock(); //mutex'i ediniyor.
		++gcount;
		lock.unlock(); // mutex'i serbest bırakıyor.
		// ...
		// mutex edinilmiş durumda ise burada destructor serbest bırakıyor
	}
}

int main() 
{
	std::jthread t1(foo);
	std::jthread t2(foo);
	t1.join();
	t2.join();
	std::cout << gcount << '\n'; //4000000

}
