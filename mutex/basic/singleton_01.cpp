#include <iostream>
#include <syncstream>
#include <thread>
#include <vector>

class ThreadUnsafeSingleton {
	inline static ThreadUnsafeSingleton* mp{};
	
	ThreadUnsafeSingleton() 
	{ 
		std::osyncstream{ std::cout } << "Initializing Singleton\n";
	}
public:
	
	ThreadUnsafeSingleton(const ThreadUnsafeSingleton&) = delete;
	ThreadUnsafeSingleton& operator=(const ThreadUnsafeSingleton&) = delete;

	static ThreadUnsafeSingleton* get_Singleton()
	{ 
		if (!mp) {
			mp = new ThreadUnsafeSingleton;
		}

		return mp;
	}
};

void foo()
{
	ThreadUnsafeSingleton* ps = ThreadUnsafeSingleton::get_Singleton();
	std::osyncstream{ std::cout } << ps << '\n';
}

int main()
{
	std::vector<std::jthread> tvec;

	for (int i = 0; i < 20; ++i)
		tvec.push_back(std::jthread(foo));
}
