#include <vector>
#include <iostream>
#include <thread>
#include <functional>

void print(const std::vector<int>& vec)
{
	for (auto i : vec)
		std::cout << i << ' ';
	std::cout << '\n';
}

int main()
{
	std::vector ivec{ 1, 2, 3, 4, 5, 6, 7 };
	//std::thread tx{ print, ivec }; //wrong - call by value
	//tx.join();
	std::thread ty{ print, ref(ivec) }; //call by reference
	ty.join();
}
