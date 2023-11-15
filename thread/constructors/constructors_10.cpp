#include <iostream>
#include <thread>

class Nec
{
public:
	Nec() = default;

	Nec(const Nec&)
	{
		std::cout << "Copy Ctor\n";
	}

	Nec(Nec&&)noexcept
	{
		std::cout << "Move Ctor\n";
	}
};

void foo(const Nec&)
{
	//...
}

void bar(Nec&&)
{
	//...
}

int main()
{
	Nec x;
	Nec y;

	std::thread tx{ foo, x}; // copy ctor
	std::thread ty{ foo, std::ref(y) }; // no copy ctor no move ctor
	std::thread tz{ bar, std::move(x) }; // move ctor
	
	tx.join();
	ty.join();
	tz.join();
}
