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
	using namespace std;

	vector ivec{ 1, 2, 3, 4, 5, 6, 7 };
	thread tx{ print, ivec }; //call by value
	tx.join();
	thread ty{ print, ref(ivec) }; //call by reference
	ty.join();
}
