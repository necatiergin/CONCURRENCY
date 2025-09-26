#include <numeric>
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <print>

int main()
{
	namespace ex = std::execution;
	using namespace std;

	vector<int> source(10);
	iota(source.begin(), source.end(), 0);
	print("{}\n", source);
	
	vector<int> dest(source.size());

	//partial_sum(source.begin(), source.end(), dest.begin());
	//inclusive_scan(ex::par, source.begin(), source.end(), dest.begin());
	//inclusive_scan(ex::unseq, source.begin(), source.end(), dest.begin());
	//inclusive_scan(ex::par_unseq, source.begin(), source.end(), dest.begin());
	print("{}\n", dest);
}
