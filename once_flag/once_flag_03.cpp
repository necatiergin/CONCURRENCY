#include <iostream>
#include <thread>
#include <mutex>

std::once_flag once_flag;

using namespace std::literals;

void foo() 
{
	std::this_thread::sleep_for(100ms);
	std::call_once(once_flag, []() { std::cout << "registered in foo" << std::endl; });
}

void bar() 
{
	std::this_thread::sleep_for(100ms);
	std::call_once(once_flag, []() { std::cout << "register in bar" << std::endl; });
}

int main()
{
	std::thread ta[10];
	for (int i = 0; i < 10; ++i) {
		ta[i] = i % 2 ? std::thread{ foo } : std::thread{ bar };
	}

	for (auto& t : ta)
		t.join();
}
