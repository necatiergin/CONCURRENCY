#include <iostream>

void func()
{
	std::cout << "func cagrildi\n";
	try
	{
		throw std::runtime_error{ "error from func\n" };
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << '\n';
	}
}

int main()
{
	try {
		std::thread t{ func };  // Hata yakalandı

		t.join();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << '\n';
	}
}
