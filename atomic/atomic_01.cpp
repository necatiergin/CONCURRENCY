#include <atomic>
#include <iostream>

int main()
{
	using namespace std;

	cout << boolalpha;
	atomic<bool> flag_1;
	atomic<bool> flag_2; //indetermined value before before C++20. false value since C++20
	cout << flag_1 << '\n';
	cout << flag_2 << '\n';
	///atomic<bool> flag_3{flag_2}; //gecersiz
	//flag_1 = flag_2; //geçersiz

	flag_1 = true;
	flag_2 = false;
	flag_1.store(false);
	flag_2.store(true);

	cout << "flag_1 = " << flag_1 << '\n';  // operator T
	cout << "flag_2 = " << flag_2 << '\n';  // operator T

	auto b = flag_1.exchange(true);
	cout << "b = " << b << '\n';
	cout << "flag_1 = " << flag_1 << '\n';  // operator T
	cout << "flag_1.load() = " << flag_1.load() << '\0';
	cout << "flag_2.load() = " << flag_2.load() << '\0';
}
