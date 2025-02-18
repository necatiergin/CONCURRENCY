#include <numeric>
#include <iostream>
#include <vector>
#include <execution>

namespace ex = std::execution;

int main()
{
	using namespace std;

	vector<int> ivec(10'000u);
	iota(ivec.begin(), ivec.end(), 0);
	
	//// her bir toplama işlemi paralel olarak yapılıyor
	//// ((0 + 1) + (2 + 3) + (4 + 5) + (6 + 7)) ...
	auto sum = std::reduce(ex::par, ivec.begin(), ivec.end(), 0);
	cout << "sum = " << sum << '\n';
}
