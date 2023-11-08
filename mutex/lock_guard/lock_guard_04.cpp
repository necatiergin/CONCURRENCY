#include <mutex>
#include <sstream>
#include <iostream>
#include <vector>
#include <thread>

struct pcout : std::stringstream {
public:
	~pcout()
	{
		std::lock_guard<std::mutex> locker{ cmutex };
		std::cout << rdbuf();
		std::cout.flush();
	}
	static inline std::mutex cmutex;
};

void print(int x)
{
	pcout{} << "print islevi x = " << x << "\n";
}

int main()
{
	std::vector<std::thread> tvec;

	for (int i = 0; i < 20; ++i)
		tvec.emplace_back(std::thread{ print, i });

	for (auto& t : tvec)
		t.join();
}
