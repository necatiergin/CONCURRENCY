// exclusive_scan

#include <vector>
#include <numeric>
#include <iostream>
#include <execution>
#include <print>

int main()
{
	std::vector ivec{ 1, 3, 5, 7, 9, 11, 13, 15 };
	print("{}\n", ivec);

	std::vector<int> dest(ivec.size());

	//exclusive_scan(std::execution::seq, ivec.begin(), ivec.end(), dest.begin(), -1);
	exclusive_scan(std::execution::par, ivec.begin(), ivec.end(), dest.begin(), -1);
	//exclusive_scan(std::execution::par_unseq, ivec.begin(), ivec.end(), dest.begin(), -1);
	//exclusive_scan(std::execution::unseq, ivec.begin(), ivec.end(), dest.begin(), -1);

	print("{}\n", dest);
}
