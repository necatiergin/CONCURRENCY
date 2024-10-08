#include <atomic>
#include <iostream>
#include <memory>

int main()
{
	boolalpha(std::cout);
	std::atomic<int> a1;
	std::cout << "a1.lock_free() : " << a1.is_lock_free() << '\n';
	std::atomic<long long> a2;
	std::cout << "a2.lock_free() : " << a2.is_lock_free() << '\n';
	std::atomic<std::shared_ptr<int>> a3; //C++20
	std::cout << "a3.lock_free() : " << a3.is_lock_free() << '\n';
}
