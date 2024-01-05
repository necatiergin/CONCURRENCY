#include <semaphore>
#include <thread>
#include <syncstream>
#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

counting_semaphore smp{ 3 };

void func()
{
	using namespace literals;
	smp.acquire();
	osyncstream{ cout } << "thread id : " << this_thread::get_id() << '\n';
	this_thread::sleep_for(3000ms);
	smp.release();
}

int main()
{
	vector<jthread> tvec;

	for (int i = 0; i < 24; ++i) {
		tvec.emplace_back(func);
	}
}
