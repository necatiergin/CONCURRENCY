#include <iostream>
#include <thread>
#include <vector>

void foo(const std::vector<int>& ivec)
{
	for (const auto val : ivec)
		std::cout << val << ' ';
}

int main()
{
	std::vector ivec{1, 2, 3, 4, 5 };

	std::thread tx{foo, std::ref(ivec)};
	tx.join();
}
