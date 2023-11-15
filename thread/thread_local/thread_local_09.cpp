#include <iostream>
#include <string>
#include <thread>
#include <mutex>

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
	std::cout << "thread id : " << id << "    x (automatic storage)  = " << x << "\n";
	std::cout << "thread id : " << id << "    y (automatic storage)  = " << y << "\n";
	std::cout << "thread id : " << id << "    z (automatic storage)  = " << z << "\n\n";
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

	thread tx{ foo,0 };
	thread ty{ foo,1 };
	thread tz{ foo,2 };
	tx.join();
	ty.join();
	tz.join();
}


Output
------
thread id : 2    x (automatic storage)  = 1
thread id : 2    y (automatic storage)  = 1
thread id : 2    z (automatic storage)  = 1

thread id : 2    x (automatic storage)  = 1
thread id : 2    y (automatic storage)  = 2
thread id : 2    z (automatic storage)  = 2

thread id : 2    x (automatic storage)  = 1
thread id : 2    y (automatic storage)  = 3
thread id : 2    z (automatic storage)  = 3

thread id : 1    x (automatic storage)  = 1
thread id : 1    y (automatic storage)  = 4
thread id : 1    z (automatic storage)  = 1

thread id : 1    x (automatic storage)  = 1
thread id : 1    y (automatic storage)  = 5
thread id : 1    z (automatic storage)  = 2

thread id : 1    x (automatic storage)  = 1
thread id : 1    y (automatic storage)  = 6
thread id : 1    z (automatic storage)  = 3

thread id : 0    x (automatic storage)  = 1
thread id : 0    y (automatic storage)  = 7
thread id : 0    z (automatic storage)  = 1

thread id : 0    x (automatic storage)  = 1
thread id : 0    y (automatic storage)  = 8
thread id : 0    z (automatic storage)  = 2

thread id : 0    x (automatic storage)  = 1
thread id : 0    y (automatic storage)  = 9
thread id : 0    z (automatic storage)  = 3
