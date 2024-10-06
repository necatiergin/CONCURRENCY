#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include <syncstream>

using namespace std::literals;

std::mutex mtx1;
std::mutex mtx2;

void foo()
{
	std::osyncstream ocout{ std::cout };
	ocout << "Thread foo trying to lock mtx1 and mtx2...\n";
	std::lock(mtx1, mtx2);				               
	ocout << "Thread foo has locked mtx1 and mtx2\n";

	std::unique_lock ulock1(mtx1, std::adopt_lock);  
	std::unique_lock ulock2(mtx2, std::adopt_lock);  
	ocout << "Thread foo has adopted both locks\n";

	std::this_thread::sleep_for(50ms);
	ocout << "Thread foo releasing mtx1 and mtx2...\n";
}

void bar() 
{
	std::osyncstream ocout{ std::cout };
	ocout << "Thread bar trying to lock mtx2 and mtx11...\n";
	lock(mtx2, mtx1);
	ocout << "Thread bar has locked mutexes mtx2 and mtx1\n";

	std::unique_lock ulock2(mtx2, std::adopt_lock);   
	std::unique_lock ulock1(mtx1, std::adopt_lock);   
	ocout << "Thread bar has adopted the locks\n";

	std::this_thread::sleep_for(50ms);
	ocout << "Thread bar releasing mutexes 2 and 1...\n";
}

int main() 
{
	std::thread tfoo(foo);
	std::thread tbar(bar);

	tfoo.join(); 
	tbar.join();
}
