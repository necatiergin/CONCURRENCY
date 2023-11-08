#include <iostream>
#include <thread>

void tfunc(int ms)
{
	using namespace std::chrono;

	std::this_thread::sleep_for(milliseconds{ ms });
	std::cout << "thread id = " << std::this_thread::get_id() << "\n";
}


int main()
{
	std::thread th{ tfunc, 2000 };
	std::cout << th.get_id() << "\n";
	th.join();
	std::cout << "program sonlaniyor\n";
}
