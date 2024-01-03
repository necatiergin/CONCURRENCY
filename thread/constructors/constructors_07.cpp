#include <iostream>
#include <thread>
#include <vector>

void foo(std::vector<int>& ivec)
{
	for (auto& val : ivec)
		val += 10;
}

int main()
{
	std::vector ivec{ 1, 2, 3, 4, 5 };

	std::thread tx{ foo, std::ref(ivec) };
	tx.join();

	for (const auto val : ivec)
		std::cout << val << ' ';
}
