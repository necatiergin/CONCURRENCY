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
	using namespace std;

	constexpr size_t size = 1'000'000u;
	mt19937 eng;

	vector<unsigned int> vec1(size);
	vector<unsigned int> vec2(size);

	eng.seed(134);
	for_each(vec1.begin(), vec1.end(), [&eng](unsigned int& x) {x = eng(); });
	eng.seed(134);
	for_each(execution::par, vec2.begin(), vec2.end(), [&eng](unsigned int& x) 
		{
			scoped_lock lock(mtx);
			x = eng(); }
		);
	
	//sort(vec1.begin(), vec1.end());
	//sort(vec2.begin(), vec2.end());

	cout << boolalpha << (vec1 == vec2);
}
