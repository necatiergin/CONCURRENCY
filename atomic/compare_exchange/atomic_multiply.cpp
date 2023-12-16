#include <atomic>
#include <iostream>

template <typename T>
T fetch_multiply(std::atomic<T>&a, T factor)
{
	T old_value = a.load();
	
	while (!a.compare_exchange_strong(old_value, old_value * factor))
		;
	
	return old_value;
}

int main() 
{
	using namespace std;

	atomic ax(6);
	cout << "ax = " << ax << '\n';
	auto pval = fetch_multiply(ax, 9);
	cout << "ax = " << ax << '\n';
	cout << "pval = " << pval << '\n';
}
