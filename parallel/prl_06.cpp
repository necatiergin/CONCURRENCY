// inclusive_scan vs. exclusive_scan

#include <numeric>
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <print>

namespace ex = std::execution;

int main()
{
	std::vector<int> svec(10);
	iota(svec.begin(), svec.end(), 0);
	std::print("{}\n", svec);
	std::vector<int> dvec1(svec.size());
	std::vector<int> dvec2(svec.size());
	inclusive_scan(ex::par, svec.begin(), svec.end(), dvec1.begin());
	std::print("{}\n", dvec1);
	exclusive_scan(ex::par, svec.begin(), svec.end(), dvec2.begin(), 100);
	std::print("{}\n", dvec2);
}
