#include <iostream>
#include <thread>
#include <chrono>
#include <cstdint>

uint64_t sum_odd = 0ull;
uint64_t sum_even = 0ull;
constexpr uint64_t n = 1'000'000'000;

void get_sum_odds()
{
	for (uint64_t i = 1; i < n; i += 2)
		sum_odd += i;
}

void get_sum_evens()
{
	for (uint64_t i = 0; i <= n; i += 2)
		sum_even += i;
}

int main()
{
	using namespace std::chrono;

	auto start = steady_clock::now();
	get_sum_evens();
	get_sum_odds();
	auto end = steady_clock::now();

	std::cout << "hesaplama tamamlandi toplam sure : " << duration_cast<milliseconds>(end - start).count() << "ms" << '\n';
	std::cout << "teklerin toplami : " << sum_odd << '\n';
	std::cout << "ciftlerin toplami : " << sum_even << '\n';
}
