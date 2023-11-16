#include <mutex>
#include <iostream>

std::mutex a_mtx;
std::mutex b_mtx;

void foo()
{
	using namespace std::literals;
	a_mtx.lock();
	std::this_thread::sleep_for(100ms);
	b_mtx.lock();
	std::cout << "func()" << std::endl;
	a_mtx.unlock();
	b_mtx.unlock();
}

void bar()
{
	using namespace std::literals;
	a_mtx.lock();
	std::this_thread::sleep_for(100ms);
	b_mtx.lock();
	std::cout << "bar()" << std::endl;
	b_mtx.unlock();
	a_mtx.unlock();
}

int main()
{
	std::thread t1{ foo };
	std::thread t2{ bar };
	t1.join();
	t2.join();
}

Geçerli kod.Deadlock yok
