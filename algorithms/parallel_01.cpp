#include <execution>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

using dsec = std::chrono::duration<double>;

constexpr std::size_t n{ 20'000'000 };

int main()
{
	std::vector<int> vec(n);
	std::mt19937 eng{ std::random_device{}() };
	std::uniform_int_distribution dist{ 0, 999'999 };
	std::generate_n(vec.begin(), n, [&] {return dist(eng); });
	auto tp_start = std::chrono::steady_clock::now();
	sort(std::execution::seq, vec.begin(), vec.end());
	auto tp_end = std::chrono::steady_clock::now();
	std::cout << dsec{ tp_end - tp_start }.count() << "saniye\n";
}

