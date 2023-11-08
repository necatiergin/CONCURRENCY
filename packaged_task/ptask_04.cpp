#include <iostream>
#include <future>  
#include <chrono>  
#include <thread>  

int countdown(int from, int to)
{
	using namespace std::literals;
	for (int i = from; i != to; --i) {
		std::cout << i << '\n';
		std::this_thread::sleep_for(1s);
	}
	std::cout << "sure bitti!\n";
	return from - to;
}

int main()
{
	std::packaged_task<int(int, int)> ptask(countdown);
	//std::future<int> ftr = ptask.get_future();
	auto ftr = ptask.get_future();

	std::thread th(std::move(ptask), 10, 0);

	int value = ftr.get();
	std::cout << "sayi suresi : " << value << " saniye\n";
	th.join();
}
