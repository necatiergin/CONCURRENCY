#include <mutex>
#include <iostream>

class Nec {
public:
	void func()
	{
		std::lock_guard guard{ mtx };
		std::cout << std::this_thread::get_id() << "  func cagrildi\n";
		foo();
		std::cout << std::this_thread::get_id() << "  func sona eriyor\n";
	}

	void foo()
	{
		std::lock_guard guard{ mtx };
		std::cout << std::this_thread::get_id() << "  foo cagrildi\n";
		std::cout << std::this_thread::get_id() << "  foo sona eriyor\n";
	}
private:
	mutable std::recursive_mutex mtx;
};


void gf()
{
	Nec nec;

	nec.func();
}

int main()
{
	std::jthread t1{ gf };
	std::jthread t2{ gf };
}
