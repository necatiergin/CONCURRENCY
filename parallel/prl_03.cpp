#include <algorithm>
#include <vector>
#include <execution>

namespace exc = std::execution;

int main()
{
	std::vector<int> vec(1'000'000u);

	///some code here
	sort(exc::seq, vec.begin(), vec.end()); // sequential
	sort(exc::par, vec.begin(), vec.end()); // parallel
	sort(exc::par_unseq, vec.begin(), vec.end()); // parallel & vectorized
	sort(exc::unseq, vec.begin(), vec.end()); // vectorized (C++20)
}
