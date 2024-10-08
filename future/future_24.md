soon
<!---
#include <future>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

void produce(std::promise<int>& px)
{
	using namespace std::literals;

	int x = 42;
	std::this_thread::sleep_for(2s);

	std::cout << "Promise sets shared state to " << x << '\n';
	px.set_value(x);
}

void consume(std::shared_future<int>& fx)
{
	auto id = std::this_thread::get_id();
	std::cout << "Thread " << id << " calling get()...\n";
	int x = fx.get();
	std::cout << "Thread " << id << " returns from calling get()\n";
	std::cout << "Thread " << id << " has answer " << x << '\n';
}

int main() 
{
	std::promise<int> prom;
	std::shared_future<int> shared_fut1 = prom.get_future();

	std::shared_future<int> shared_fut2 = shared_fut1;

	std::jthread tprod(produce, std::ref(prom));

	std::jthread tcon1(consume, std::ref(shared_fut1));
	std::thread tcon2(consume, std::ref(shared_fut2));
}
--->
