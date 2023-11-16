#include <chrono>
#include <future>
#include <iostream>

int main()
{
	auto tp_start = std::chrono::system_clock::now();
	auto lazy_async = std::async(std::launch::async, [] {return std::chrono::system_clock::now(); });
	auto eager_async = std::async(std::launch::async, [] {return std::chrono::system_clock::now(); });

	std::this_thread::sleep_for(std::chrono::seconds(1));
	
	using dsec = std::chrono::duration<double>;
	auto deferred_sec = static_cast<dsec>(lazy_async.get() - tp_start).count();
	auto eager_sec = static_cast<dsec>(eager_async.get() - tp_start).count();
	
	std::cout << "duration for deferred in sec : " << deferred_sec << '\n';
	std::cout << "duration for eager in sec : " << eager_sec << '\n';
}
