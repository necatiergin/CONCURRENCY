#include <iostream>
#include <thread>

void func(int) {std::cout << "func(int)\n";}
void func(double) {std::cout << "func(double)\n";}

int main()
{
	//std::thread t1{func, 12};  //invalid
	//std::thread t2{func, 1.2};  //invalid
	std::thread t3{static_cast<void(*)(int)>(func), 12};
	std::thread t4{static_cast<void(*)(double)>(func), 12};
	t3.join();
	t4.join();
}
