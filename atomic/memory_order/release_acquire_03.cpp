#include <atomic>
#include <string>
#include <thread>
#include <cassert>

std::atomic_bool flag1 = false;
std::atomic_bool flag2 = false;
std::atomic_bool flag3 = false;
std::string name{};

void foo()
{
	name = "necati";
	flag1.store(true, std::memory_order_release);
}

void bar()
{
	while (!flag1.load(std::memory_order_acquire))
		;

	name += " ergin";
	flag2.store(true, std::memory_order_release);
}

void baz()
{
	while (!flag2.load(std::memory_order_acquire))
		;

	name += " can";
}


void test()
{
	flag1 = false;
	flag2 = false;
	flag3 = false;

	std::thread t1{ foo };
	std::thread t2{ bar };
	std::thread t3{ baz };

	t1.join();
	t2.join();
	t3.join();

	assert(name == "necati ergin can");
}

int main()
{
	for (int i = 0; i < 1000; ++i) {
		test();
	}
}
