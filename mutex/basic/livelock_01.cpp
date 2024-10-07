#include <mutex>
#include <thread>
#include <iostream>
#include <chrono>

using namespace std::literals;

std::mutex mtx1, mtx2;

void foo()
{
	std::this_thread::sleep_for(10ms);
	bool is_locked{ false };
	while (!is_locked) {
		std::lock_guard lock(mtx1); 
		std::cout << "Onden buyurun Hasan Bey!\n";
		std::this_thread::sleep_for(1s);
		is_locked = mtx2.try_lock();
	}
	if (is_locked)
		std::cout << "thread foo has locked both mtx1 and mtx2\n";
}

void bar() 
{
	bool is_locked = false;
	while (!is_locked) {
		std::lock_guard lock (mtx2);
		std::cout << "Onden buyurun Ahmet Bey!\n";
		std::this_thread::sleep_for(1s);
		is_locked = mtx1.try_lock();
	}
	if (is_locked)
		std::cout << "threadbar has locked both mutx2 and mtx1\n";
}

int main() 
{
	std::thread tfoo(foo);
	std::this_thread::sleep_for(20ms);
	std::thread tbar(bar);

	tfoo.join(); 
	tbar.join();
}
