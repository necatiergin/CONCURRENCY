#include <atomic>
#include <iostream>
#include <memory>


int main()
{
	using namespace std;

	boolalpha(cout);
	atomic<int> a1;
	cout << "a1.lock_free() : " << a1.is_lock_free() << '\n';
	atomic<long long> a2;
	cout << "a2.lock_free() : " << a2.is_lock_free() << '\n';
	atomic<shared_ptr<int>> a3; //C++20
	cout << "a3.lock_free() : " << a3.is_lock_free() << '\n';
}
