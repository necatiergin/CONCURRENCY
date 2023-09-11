/*
	we can move an object to the function that our thread will run.
*/

#include <vector>
#include <iostream>
#include <thread>

void func(std::vector<int>&& vec)
{
	for (auto i : vec)
		std::cout << i << ' ';
	std::cout << '\n';
}

int main()
{
	using namespace std;

	vector<int> ivec{ 1, 2, 3, 4, 5, 6, 7 };
	thread tx{ func, move(ivec) }; //moving
	tx.join();
	cout << "ivec.size() = " << ivec.size() << '\n';
}
