#include <thread>
#include <iostream>
#include <chrono>

void func()
{
	std::cout << "func\n";
	std::this_thread::sleep_for(std::chrono::seconds(5));
}

int main()
{
	std::cout << std::boolalpha;
	std::thread t{ func };
	std::cout << t.joinable() << '\n'; // true
	t.join();	
	std::cout << t.joinable() << '\n'; //  false
}
