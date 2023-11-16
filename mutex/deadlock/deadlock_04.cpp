#include<mutex>
#include <iostream>

std::mutex a_mtx;
std::mutex b_mtx;

void foo()
{
	using namespace std::literals;
	std::lock(a_mtx, b_mtx);	
	std::lock_guard guard1{ a_mtx, std::adopt_lock };  
	std::lock_guard guard2{ b_mtx, std::adopt_lock };  
	std::this_thread::sleep_for(100ms);
	std::cout << "foo()" << std::endl;
}

void bar()
{
	using namespace std::literals;
	std::lock(a_mtx, b_mtx);
	std::lock_guard guard1{ a_mtx, std::adopt_lock };
	std::lock_guard guard2{ b_mtx, std::adopt_lock };
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
