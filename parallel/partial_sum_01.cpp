#include <numeric>
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	using namespace std;

	vector<int> src_vec(100);
	iota(src_vec.begin(), src_vec.end(), 0);
	copy(src_vec.begin(), src_vec.end(), ostream_iterator<int>{cout, " "});
	cout << "\n\n";
	vector<int> dest_vec(src_vec.size());

	std::partial_sum(src_vec.begin(), src_vec.end(), dest_vec.begin());
	
	copy(dest_vec.begin(), dest_vec.end(), ostream_iterator<int>{cout, " "});
	cout << "\n\n";
}
