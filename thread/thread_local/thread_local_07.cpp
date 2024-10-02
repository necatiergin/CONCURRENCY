#include <syncstream>
#include <iostream>
#include <chrono>

class Myclass {
public:
	Myclass()
	{
		std::osyncstream{ std::cout } << "Myclass constructor this : " << this << '\n';
	}

	~Myclass()
	{
		std::osyncstream{ std::cout } << "Myclass destructor this : " << this << '\n';
	}
};

void foo()
{
	std::osyncstream{ std::cout } << "foo called\n";
	thread_local Myclass m;
	std::osyncstream{ std::cout } << "foo ends\n";
}

void bar()
{
	using namespace std::chrono_literals;
	std::osyncstream{ std::cout } << "bar called\n";
	foo();
	std::this_thread::sleep_for(3s);
	std::osyncstream{ std::cout } << "bar ends\n";
}

int main()
{
	std::thread t{ bar };

	t.join();
}

/*
 a local object may be thread-local.
its life ends when the thread terminates
*/
