//moving of threads

#include <thread>
#include <iostream>
#include <utility>

std::thread make_thread() 
{
	return std::thread([]() {
	std::cout << "Necati Ergin!\n";
	});
}

std::thread func(std::thread t) 
{
	//...
	return t;
}

int main() 
{
	std::thread t1(make_thread());
	std::thread t2(std::move(t1));
	t1 = std::move(t2);
	t1 = func(std::move(t1));
	t1.join();
}
