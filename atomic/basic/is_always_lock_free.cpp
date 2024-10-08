#include <atomic>
#include <iostream>

struct Nec {
	short x, y, z, t;
};

int main()
{
	constexpr auto b1 = std::atomic<int>::is_always_lock_free;
	constexpr auto b2 = std::atomic<long>::is_always_lock_free;
	constexpr auto b3 = std::atomic<Nec>::is_always_lock_free;
}
