#include <numeric>
#include <vector>
#include <future>
#include <algorithm>
#include <random>
#include <iostream>

using uint64 = unsigned long long;

uint64 accummulate_s(const uint64* first, const uint64* last)
{
	return std::accumulate(first, last, 0ull);
}

uint64 acc_parrallel(const std::vector<uint64>& vec)
{
	using task_t = uint64(const uint64*, const uint64*);
	const auto data = vec.data();
	const auto size = vec.size();

	std::packaged_task<task_t> task1(accummulate_s);
	std::packaged_task<task_t> task2(accummulate_s);
	std::packaged_task<task_t> task3(accummulate_s);
	std::packaged_task<task_t> task4(accummulate_s);


	auto ft1 = task1.get_future();
	auto ft2 = task2.get_future();
	auto ft3 = task3.get_future();
	auto ft4 = task4.get_future();
	
	std::jthread t1(std::move(task1), data, data + size / 4);
	std::jthread t2(std::move(task2), data + size / 4, data + 2 * (size / 4));
	std::jthread t3(std::move(task3), data + 2 * (size / 4), data + 3 * (size / 4));
	std::jthread t4(std::move(task4), data + 3 * (size / 4), data + size);

	return ft1.get() + ft2.get() + ft3.get() + ft4.get();
}


int main()
{
	using namespace std;
	using namespace chrono;

	vector<uint64> uvec(1'000'000u);
	mt19937 eng;
	uniform_int_distribution dist{ 0ull, 100ull};

	generate(uvec.begin(), uvec.end(), [&] {return dist(eng); });

	//auto sum = accumulate(uvec.begin(), uvec.end(), 0ull);
	auto sum = acc_parrallel(uvec);

	cout << "sum = " << sum << '\n';
}
