#include <mutex>

std::mutex mtx;

void foo()
{
	while (!mtx.try_lock()) {
		//do something else
		//and try to lock the mutex again
	}

	{
		//criticial section
		//some code here
	}
}
