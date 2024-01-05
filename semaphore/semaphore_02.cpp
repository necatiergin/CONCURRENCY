#include <semaphore>
#include <thread>
#include <syncstream>
#include <iostream>
#include <chrono>
#include <vector>

using namespace std;
using namespace literals;

counting_semaphore smp{ 3 };

void foo()
{
	smp.acquire();
	osyncstream{ cout } << "thread id in foo: " << this_thread::get_id() << '\n';
	this_thread::sleep_for(3000ms);
	smp.release();
}


void bar()
{
	smp.acquire();
	osyncstream{ cout } << "thread id in bar : " << this_thread::get_id() << '\n';
	this_thread::sleep_for(3000ms);
	smp.release();
}

int main()
{
	vector<jthread> tvec;

	for (int i = 0; i < 24; ++i) {
		if (i % 2)
			tvec.emplace_back(foo);
		else
			tvec.emplace_back(bar);
	}
}
