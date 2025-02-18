#include <numeric>
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

namespace ex = std::execution;

int main()
{
	using namespace std;

	const auto print = [] (const auto& c){
		copy(c.begin(), c.end(), ostream_iterator<int>{cout, " "});
		cout << '\n';
		};
	
	vector<int> svec(20);
	iota(svec.begin(), svec.end(), 0);
	print(svec);
	vector<int> dvec1(svec.size());
	vector<int> dvec2(svec.size());
	inclusive_scan(ex::par, svec.begin(), svec.end(), dvec1.begin());
	print(dvec1);
	exclusive_scan(ex::par, svec.begin(), svec.end(), dvec2.begin(), 1000);
	print(dvec2);
}
