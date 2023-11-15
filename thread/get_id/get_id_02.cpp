#include <iostream>
#include <thread>

using namespace std;
std::thread::id main_thread_id;

void func()
{
	auto id = std::this_thread::get_id();
	if (id == main_thread_id)
	{
		std::cout << "Func ana thread tarafindan calistiriliyor\n";
	}
	else
	{
	std:cout << "Func child thread tarafindan calistiriliyor\n";
	}
}

int main()
{
	main_thread_id = this_thread::get_id();
	func();

	thread tx{ func };
	tx.join();
}
