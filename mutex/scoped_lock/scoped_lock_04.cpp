#include<mutex>
#include <iostream>

std::mutex a_mtx;
std::mutex b_mtx;

void foo()
{
	using namespace std::literals;
	std::scoped_lock guard{ a_mtx, b_mtx };
	std::this_thread::sleep_for(100ms);
	std::cout << "func()" << std::endl;
}

void bar()
{
	using namespace std::literals;
	std::scoped_lock guard{ a_mtx, b_mtx };
	std::this_thread::sleep_for(100ms);
	std::cout << "bar()" << std::endl;
}

int main()
{
	std::thread t1{ foo };
	std::thread t2{ bar };
	t1.join();
	t2.join();
}
