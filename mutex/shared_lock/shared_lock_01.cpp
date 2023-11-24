#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <shared_mutex>
#include <syncstream>

using namespace std::literals;

int cnt = 0;
std::shared_mutex mtx;

 void writer() 
 {
	for (int i = 0; i < 10; ++i) {
		{
			std::scoped_lock lock(mtx);
			++cnt;
		}
		std::this_thread::sleep_for(100ms);
	}
}

 void reader() 
 {
	for (int i = 0; i < 100; ++i) {
		int c;
		{
			std::shared_lock lock(mtx);
			c = cnt;
		}
		std::osyncstream{ std::cout } << std::this_thread::get_id() << ' ' << c << '\n';
		std::this_thread::sleep_for(10ms);
	}
}

 int main() 
 {
	 std::vector<std::jthread> tvec;

	tvec.reserve(16);
	tvec.emplace_back(writer);

	for (int i = 0; i < 16; ++i) 
		tvec.emplace_back(reader);

}
