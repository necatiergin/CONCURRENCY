#include <vector>
#include <numeric>
#include <iostream>

int main()
{
	using namespace std;

    vector<int> ivec{ 1, 3, 5, 7, 9 };

	auto x = reduce(ivec.begin(), ivec.end(), 0);
	//auto y = reduce(ivec.begin(), ivec.end());
	auto y = reduce(ivec.begin(), ivec.end(), int{});

	cout << "x = " << x << '\n';
	cout << "y = " << y << '\n';

}
