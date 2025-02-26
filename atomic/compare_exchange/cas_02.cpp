#include <atomic>
#include <iostream>

int main()
{
	using std::cout, std::boolalpha, std::atomic;

	int a[] = { 1, 3, 5, 7 };
	atomic<int*> p = a;
	cout << "*p = " << *p << '\n';
	p.store(a + 1);
	cout << "*p = " << *p << '\n';
	int* q{ a + 1 };
	cout << "*q = " << *q << '\n';
	bool result = p.compare_exchange_strong(q, a + 3);
	cout << "result = " << result << '\n';
	cout << "*p = " << *p << '\n';
	result = p.compare_exchange_strong(q, a);
	cout << "result = " << result << '\n';
	cout << "*p = " << *p << '\n';
	cout << "*q = " << *q << '\n';
}

