#include <atomic>
#include <iostream>
#include <concepts>

int main()
{
	constexpr auto b1 = std::same_as<std::atomic<int>,  std::atomic_int>;
	constexpr auto b2 = std::same_as<std::atomic<char>, std::atomic_char>;
	constexpr auto b3 = std::same_as<std::atomic<long>, std::atomic_long>;

	constexpr auto result = b1 && b2 && b3; //true
}
