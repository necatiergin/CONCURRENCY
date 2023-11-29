#include <atomic>
#include <iostream>

int main()
{
	using namespace std;

	cout << boolalpha;
	// atomic_flag flag_x{ false }; //gecersiz
	// atomic_flag flag_y{ true };  //gecersiz
	atomic_flag flag_z; //C++ 17'de belirsiz deger C++20'de false değeri
	cout << "flag_z = " << flag_z.test() << "\n"; //C++20
	atomic_flag flag = ATOMIC_FLAG_INIT;  //gecerli
	cout << "flag = " << flag.test() << "\n"; //C++20
	auto b = flag.test_and_set();
	cout << "b = " << b << "\n";
	cout << "flag = " << flag.test() << "\n";
	flag.clear();
	cout << "flag = " << flag.test() << "\n";
	b = flag.test_and_set();
	cout << "b = " << b << "\n";
	cout << "flag = " << flag.test() << "\n";
}



