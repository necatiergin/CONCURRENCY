#include <atomic>
#include <concepts>

template <std::integral T>
void atomic_inc(std::atomic<T>&x) 
{
	T val{ x };
	while (!x.compare_exchange_weak(val, val + 1)) {}
}

