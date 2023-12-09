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
	std::vector<double> vec(n);
	std::mt19937 eng{ std::random_device{}() };
	std::uniform_real_distribution dist{ -20., 20.};
	std::generate(vec.begin(), vec.end(), [&] {return dist(eng); });
	auto tp_start = std::chrono::steady_clock::now();
	//sort(std::execution::seq, vec.begin(), vec.end());
	//sort(std::execution::unseq, vec.begin(), vec.end());
	//sort(std::execution::par, vec.begin(), vec.end());
	//sort(std::execution::par_unseq, vec.begin(), vec.end());
	auto tp_end = std::chrono::steady_clock::now();
	std::cout << dsec{ tp_end - tp_start }.count() << " saniye\n";
}
