#include <numeric>
#include <vector>
#include <future>
#include <algorithm>
#include <random>
#include <iostream>
#include <chrono>

using uint64 = unsigned long long;

uint64 accummulate_s(const uint64* first, const uint64* last)
{
	return std::accumulate(first, last, 0ull);
}

uint64 acc_parrallel(const std::vector<uint64>& vec)
{
	const auto data = vec.data();
	const auto size = vec.size();

	auto ft1 = std::async(std::launch::async, accummulate_s, data, data + size / 4);
	auto ft2 = std::async(std::launch::async, accummulate_s, data + size / 4, data + 2 * (size / 4));
	auto ft3 = std::async(std::launch::async, accummulate_s, data + 2 * (size / 4), data + 3 * (size / 4));
	auto ft4 = std::async(std::launch::async, accummulate_s, data + 3 * (size / 4), data + size);

	return ft1.get() + ft2.get() + ft3.get() + ft4.get();
}


int main()
{
	using namespace std;
	using namespace chrono;

	vector<uint64> uvec(50'000'000u);
	mt19937 eng;
	uniform_int_distribution dist{ 0ull, 100ull };

	generate(uvec.begin(), uvec.end(), [&] {return dist(eng); });

	auto tp_start = steady_clock::now();
	auto sum = accumulate(uvec.begin(), uvec.end(), 0ull);
	//auto sum = acc_parrallel(uvec);
	auto tp_end = steady_clock::now();

	cout << duration<double>(tp_end - tp_start) << '\n';

	cout << "sum = " << sum << '\n';
}
