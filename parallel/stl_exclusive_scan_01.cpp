#include <vector>
#include <numeric>
#include <iostream>
#include <execution>

int main()
{
	using namespace std;

	vector svec{ 1, 3, 5, 7, 9, 11, 13, 15 };
	vector<int> dvec(svec.size());

	inclusive_scan(std::execution::par, svec.begin(), svec.end(), dvec.begin());

	for (auto i : dvec) cout << i << ' ';
	cout << '\n';
	exclusive_scan(std::execution::par, svec.begin(), svec.end(), dvec.begin(), -1);
	for (auto i : dvec) cout << i << ' ';
	cout << '\n';
}
