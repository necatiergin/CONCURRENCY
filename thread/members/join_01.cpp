//eğer std::thread nesnesinin destructor'u çağrıldığında thread joinable durumda ise std::terminate işlevi çağrılır.

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
