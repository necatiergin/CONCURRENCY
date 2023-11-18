#include <mutex>
#include <iostream>
#include <thread>

std::recursive_mutex rmtx;
int gcount = 0;

void rfunc(char c, int n)
{
	if (n < 0)
		return;

	rmtx.lock();
	std::cout << c << ' ' << gcount++ << '\n';
	rfunc(c, n - 1);
	rmtx.unlock();
}

int main()
{
	std::thread tx{ rfunc, 'x', 10 };
	std::thread ty{ rfunc, 'y', 10 };
	tx.join();
	ty.join();
}
