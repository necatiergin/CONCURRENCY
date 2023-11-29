#include <atomic>
#include <iostream>

int main()
{
	using namespace std;

	cout << boolalpha;
	atomic<int> a;

	cout << "a = " << a << "\n";
	cout << "a.load() = " << a.load() << "\n";
	a.store(10);
	cout << "a = " << a << "\n";
	int expected = 10;
	cout << "expected = " << expected << "\n";
	bool result = a.compare_exchange_strong(expected, 50);
	// a has the expected value and will be set
	cout << "a = " << a << "\n";
	//result will be true
	cout << "result = " << result << "\n";
	//expected will not be set
	cout << "expected = " << expected << "\n";
}
