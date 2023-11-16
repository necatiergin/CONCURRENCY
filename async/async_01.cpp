#include <iostream>
#include <chrono>
#include <future>

int main()
{
	using namespace std::chrono_literals;
	
	std::chrono::time_point start = std::chrono::steady_clock::now();

	auto eager = std::async(std::launch::async, [] {return std::chrono::steady_clock::now(); });
	auto lazy = std::async(std::launch::deferred, [] {return std::chrono::steady_clock::now(); });

	std::this_thread::sleep_for(1s);

	using dsec = std::chrono::duration<double>;
	auto deferred_sec = duration_cast<dsec>(lazy.get() - start).count();
	auto eager_sec = duration_cast<dsec>(eager.get() - start).count();

	std::cout << "duration for deferred in sec : " << deferred_sec << '\n';
	std::cout << "duration for eager in sec : " << eager_sec << '\n';
}
