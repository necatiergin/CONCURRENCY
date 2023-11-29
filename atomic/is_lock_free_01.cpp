#include <atomic>
#include <iostream>

int main()
{
	std::cout.setf(std::ios::boolalpha);
	std::atomic<int> x;
	//std::atomic<long long int> x;
	
	std::cout << x.is_lock_free() << "\n";
}
