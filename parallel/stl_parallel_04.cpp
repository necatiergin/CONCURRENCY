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

	vector<int> ivec(100'000);
	int cnt{};

	for_each(ex::par, ivec.begin(), ivec.end(), [&cnt](int& x) { x = ++cnt; });

	std::ofstream ofs{ "out.txt" };
	if (!ofs) {
		std::cerr << "out.txt dosyasi olusturulamadi\n";
		exit(EXIT_FAILURE);
	}

	cout << "cnt = " << cnt << '\n';

	copy(ivec.begin(), ivec.end(), ostream_iterator<int>{ofs, "\n"});
}
