#include <mutex>
#include <chrono>
#include <thread>
#include <iostream>

int gcounter{};
std::timed_mutex mtx;

void increment(int i)
{
	using namespace std::literals;

	if (mtx.try_lock_for(50ms)) {
		++gcounter;
		std::this_thread::sleep_for(10ms);
		std::cout << "thread : " << i << " kritik bolgeye girdi\n";
		mtx.unlock();
	}
	else
		std::cout << "thread  " << i << " kritik bolgeye giremedi\n";
}

int main()
{
	std::thread t1{ increment, 1 };
	std::thread t2{ increment, 2 };

	t1.join();
	t2.join();

	std::cout << "gcounter = " << gcounter << '\n';
}
