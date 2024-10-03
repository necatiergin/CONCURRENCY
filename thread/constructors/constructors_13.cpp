#include <thread>
#include <iostream>

void func(int)
{
	std::cout << "void func(int)\n";
}

void func(int, int)
{
	std::cout << "void func(int, int)\n";
}


void func(double)
{
	std::cout << "void func(double)\n";
}

int main()
{
	using fptype_1 = void(*)(int);
	using fptype_2 = void(*)(int, int);
	using fptype_3 = void(*)(double);

	fptype_1 fp1 = &func;
	fptype_2 fp2 = &func;
	fptype_3 fp3 = &func;

	std::thread th1{ fp1, 1 };
	th1.join();
	std::thread th2{ fp2, 1, 2};
	th2.join();
	std::thread th3{ fp3, 1.11 };
	th3.join();
}
