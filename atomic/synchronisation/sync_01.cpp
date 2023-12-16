
#include <condition_variable>
#include <iostream>
#include <thread>
#include <string>

std::string shared;
std::mutex mtx;
std::condition_variable cv;

bool ready{ false };

void consumer() 
{
	std::unique_lock lck(mtx);
	cv.wait(lck, [] { return ready; });
	std::cout << "shared is : " << shared << '\n';
}

void producer() 
{
	shared = "necati ergin";
	{
		std::scoped_lock lck(mtx);
		ready = true;
	}
	cv.notify_one();
}

int main() 
{
	{
		std::jthread t1(producer);
		std::jthread t2(consumer);
	}

}
