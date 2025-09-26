// data race

#include <algorithm>
#include <vector>
#include <iostream>
#include <execution>
#include <fstream>
#include <iterator>

namespace ex = std::execution;

int main()
{
	using namespace std;

	vector<int> ivec(1'000'000);
	int cnt{};

	for_each(ex::par, ivec.begin(), ivec.end(), [&cnt](int& x) { x = ++cnt; });

	cout << "cnt = " << cnt << '\n';
}
