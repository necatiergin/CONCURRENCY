
#include <mutex>
#include <iostream>

int x{};
std::mutex mtx_func;
std::mutex mtx_foo;

void func()
{
	std::lock_guard guard{mtx_func};
	for(int i = 0; i < 1000;++i)
	{
		++x;
	}
}
void foo()
{
	std::lock_guard guard{mtx_foo};
	for(int i = 0; i < 1000;++i)
	{
		++x;
	}
}

int main()
{
	std::thread t1{func};
	std::thread t2{foo};
	t1.join();
	t2.join();
}

X in değerinin 2000 olma garantisi yok
Kod problemli.
