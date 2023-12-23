#include <atomic>
#include <iostream>

int main()
{
	using namespace std;
	atomic<int> x{};
	x.store(98);
	cout << x.load() << '\n';
	atomic_store(&x, 30);
	cout << atomic_load(&x) << '\n';
	//
}	
