//from cppreference.com

#include <mutex>
#include <random>
#include <vector>
#include <algorithm>
#include <execution>
#include <iostream>

std::mutex mtx;

int main()
{
	constexpr size_t size = 1'000'000u;

	std::vector<unsigned int> vec1(size);
	std::vector<unsigned int> vec2(size);

	std::mt19937 eng(134u);
	for_each(vec1.begin(), vec1.end(), [&eng](unsigned int& x) {x = eng(); });
	eng.seed(134u);
	for_each(std::execution::par, vec2.begin(), vec2.end(), [&eng](unsigned int& x)
		{
			std::scoped_lock lock(mtx);
			x = eng(); 
		}
	);

	sort(vec1.begin(), vec1.end());
	sort(vec2.begin(), vec2.end());

	std::cout << std::boolalpha << (vec1 == vec2);
}
