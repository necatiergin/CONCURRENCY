#include <atomic>
#include <iostream>

int main()
{
	using namespace std;

	atomic x = 5;
	atomic y = 5;

	auto r1 = x += 2;
	auto r2 = y.fetch_add(2);

	cout << "r1 = " << r1 << '\n'; //7
	cout << "r2 = " << r2 << '\n'; //5
}
