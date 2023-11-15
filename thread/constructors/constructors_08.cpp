#include <iostream>
#include <functional>
#include <thread>

void foo(int& r)
{
	++r;
}

int main()
{
	int x{ 43 };

	//std::thread tx{foo, x}; //invalid

	std::thread ty{foo, std::ref(x) };  // valid
	ty.join();
	
	std::cout << "x = " << x << '\n';
}
