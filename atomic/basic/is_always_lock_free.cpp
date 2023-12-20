#include <atomic>
#include <iostream>
#include <thread>

struct Nec {
	short x, y, z, t;
};

int main()
{
	using namespace std;

	constexpr auto b1 = atomic<int>::is_always_lock_free;
	constexpr auto b2 = atomic<long>::is_always_lock_free;
	constexpr auto b3 = atomic<Nec>::is_always_lock_free;
}	
