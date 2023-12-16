
#include <condition_variable>
#include <iostream>
#include <thread>
#include <string>

std::string shared;

std::atomic ready{ false };

void consumer() 
{
	while (!ready)
		;

	std::cout << "shared is : " << shared << '\n';

}

void producer() 
{
	shared = "necati ergin";
	ready = true;
}

int main() 
{
	{
		std::jthread t1(producer);
		std::jthread t2(consumer);
	}

}
