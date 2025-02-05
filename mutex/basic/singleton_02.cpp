#include <iostream>
#include <syncstream>
#include <thread>
#include <vector>

class ThreadSafeSingleton {
	inline static ThreadSafeSingleton* mp{};

	ThreadSafeSingleton()
	{
		std::osyncstream{ std::cout } << "Initializing Singleton\n";
	}
public:

	ThreadSafeSingleton(const ThreadSafeSingleton&) = delete;
	ThreadSafeSingleton& operator=(const ThreadSafeSingleton&) = delete;

	static ThreadSafeSingleton& get_Singleton()
	{
		static ThreadSafeSingleton s;

		return s;
	}
};

void foo()
{
	ThreadSafeSingleton& rs = ThreadSafeSingleton::get_Singleton();
	std::osyncstream{ std::cout } << &rs << '\n';
}

int main()
{
	std::vector<std::jthread> tvec;

	for (int i = 0; i < 20; ++i)
		tvec.push_back(std::jthread(foo));
}
