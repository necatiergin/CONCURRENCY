#include <atomic>
#include <iostream>
#include <concepts>

int main()
{
	using namespace std;

	constexpr auto b1 = same_as<atomic<int>, atomic_int>;
	constexpr auto b2 = same_as<atomic<char>, atomic_char>;
	constexpr auto b3 = same_as<atomic<long>, atomic_long>;

	constexpr auto result = b1 && b2 && b3; //true
}	
