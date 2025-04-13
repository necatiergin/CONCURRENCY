#include <iostream>
#include <thread>

int main()
{
	std::cout <<
		typeid(std::this_thread::get_id()).name();

	// sample output: class std::thread::id;	
}
