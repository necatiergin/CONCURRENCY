#include <numeric>
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

namespace ex = std::execution;
int main()
{
	using namespace std;

	vector<int> src_vec(100);
	iota(src_vec.begin(), src_vec.end(), 0);
	copy(src_vec.begin(), src_vec.end(), ostream_iterator<int>{cout, " "});
	cout << "\n\n";
	vector<int> dest_vec(src_vec.size());

	exclusive_scan(ex::par, src_vec.begin(), src_vec.end(), dest_vec.begin(), -1);
	copy(dest_vec.begin(), dest_vec.end(), ostream_iterator<int>{cout, " "});
	cout << "\n\n";
}
