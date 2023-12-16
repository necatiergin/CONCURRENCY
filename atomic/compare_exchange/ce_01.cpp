#include <atomic>
#include <iostream>

int main()
{
	using namespace std;

	cout << boolalpha;
	atomic<int> a;

	cout << "a = " << a << '\n';
	cout << "a.load() = " << a.load() << '\n';
	a.store(10);
	cout << "a = " << a << '\n';
	int expected = 20;
	cout << "expected = " << expected << '\n';
	bool result = a.compare_exchange_strong(expected, 50);
	// a has not the expected value and will not be set
	cout << "a = " << a << '\n';
	//result will be false
	cout << "result = " << result << '\n';
	//expected will be set to the value of a
	cout << "expected = " << expected << '\n';
}
