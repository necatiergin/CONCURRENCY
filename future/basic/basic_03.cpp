//std::future<T>::set_value

#include <future>
#include <iostream>
#include <thread>

int foo(int x)
{
	//code
	return x * x + 5;
}

int main()
{
	std::promise<int> prom;
	auto ft = prom.get_future();
	std::jthread tx{ [&](int val) {prom.set_value(foo(val)); }, 20 };

	std::cout << ft.get() << '\n';
}
