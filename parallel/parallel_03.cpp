#include <algorithm>
#include <vector>
#include <execution>

namespace se = std::execution;

int main()
{
	std::vector<int> vec(1'000'000u);

	///some code here
	sort(se::seq, vec.begin(), vec.end()); // sequential
	sort(se::par, vec.begin(), vec.end()); // parallel
	sort(se::par_unseq, vec.begin(), vec.end()); // parallel & vectorized
	sort(se::unseq, vec.begin(), vec.end()); // vectorized (C++20)
}
