#include <iostream>
#include <thread>
#include <future>
#include <utility>
#include <chrono>

using namespace std::literals;

int get_value() 
{
	std::this_thread::sleep_for(500ms);
	return 333;
}

int main() 
{
	std::packaged_task<int()> ptask(get_value);

	auto ftr = ptask.get_future();
	std::jthread th(std::move(ptask));
	th.detach();
	int result = ftr.get();
	std::cout << "the value is : " << result;
}
