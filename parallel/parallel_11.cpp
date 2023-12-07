#include <vector>
#include <execution>
#include <algorithm>
#include <iostream>
#include <stdexcept>

int main()
{
	std::vector<int> ivec{ 5, 7, 9, 2, 4, 6, 8, 10, 3, 1};

	try {
		for_each(std::execution::seq, ivec.begin(), ivec.end(), [](int x) {
			if (x == 8)
				throw std::runtime_error{ "8 is not allowed" }; //std::terminate
			std::cout << x << '\n';
			});
	}
	catch (const std::exception& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
	}
}

