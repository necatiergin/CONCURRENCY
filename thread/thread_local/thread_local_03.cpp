#include <mutex>
#include <iostream>

std::mutex mtx;

void func(int id)
{
	int x = 0;
	static int y = 0;
	thread_local int z = 0;

	++x;
	++z;
	std::lock_guard guard(mtx);
	++y;
	std::cout << "thread id : " << id << " x (automatic storage)     = " << x << "\n";
	std::cout << "thread id : " << id << " y (static storage)        = " << y << "\n";
	std::cout << "thread id : " << id << " z (thread local storage)  = " << z << "\n\n";
}

void foo(int id)
{
	func(id);
	func(id);
	func(id);
}

int main()
{
	using namespace std;

	thread tx{ foo, 0 };
	thread ty{ foo, 1 };
	thread tz{ foo, 2 };

	tx.join();
	ty.join();
	tz.join();
}
