//if the destructor of a std::thread object is called in a joinable state std::terminate is called

#include <iostream>
#include <thread>

void func()
{
	std::cout << "hello from func!\n";
}

void myterminate()
{
	std::cout << "myterminate\n";
	(void)getchar();
	std::abort();
}

int main()
{
	set_terminate(myterminate);
	std::thread t(func);
	//t.join();
}
