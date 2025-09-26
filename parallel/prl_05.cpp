#include <execution>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

template <typename E, typename T>
double measure_duration(E policy, std::vector<T>& vec)
{
	using dsec = std::chrono::duration<double, std::milli>;
	auto tp_start = std::chrono::steady_clock::now();
	std::replace_if(policy, vec.begin(), vec.end(), [](int x) {return x % 2 == 0; }, 0);
	auto tp_end= std::chrono::steady_clock::now();
	return dsec{ tp_end - tp_start }.count();
}

int main()
{
	constexpr std::size_t n{ 20'000'000 };
	std::vector<int> vec(n);
	std::mt19937 eng{ std::random_device{}() };
	std::uniform_int_distribution dist{ 0, 10'000'000};
	std::generate(vec.begin(), vec.end(), [&] {return dist(eng); });

	auto data_seq = vec;
	auto data_unseq = vec;
	auto data_par = vec;
	auto data_par_unseq = vec;

	double d1 = measure_duration(std::execution::seq, data_seq);
	double d2 = measure_duration(std::execution::unseq, data_unseq);
	double d3 = measure_duration(std::execution::par, data_par);
	double d4 = measure_duration(std::execution::par_unseq, data_par_unseq);

	std::cout << "sequential            : " << d1 << " milliseconds\n";
	std::cout << "unsequential          : " << d2 << " milliseconds\n";
	std::cout << "parallel              : " << d3 << " milliseconds\n";
	std::cout << "parallel unsequential : " << d4 << " milliseconds\n";
}
