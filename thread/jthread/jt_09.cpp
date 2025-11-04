#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <syncstream>

using namespace std::literals::chrono_literals;


void f(std::stop_token token, char c)
{
	while (!token.stop_requested()) {
		std::cout.put(c);
		std::this_thread::sleep_for(10ms);
	}
	
	std::osyncstream{ std::cout } << "\nthread id " << std::this_thread::get_id() << " is out of the loop";
}

int main()
{
	std::stop_source source;

	auto token = source.get_token();

	std::vector<std::thread> tvec;
	tvec.reserve(26);
	for (int i = 0; i < 26; ++i) {
		tvec.emplace_back(f, token, 'A' + i);
	}

	std::this_thread::sleep_for(3000ms);
	source.request_stop();

	for (auto& t : tvec)
		t.join();
}
