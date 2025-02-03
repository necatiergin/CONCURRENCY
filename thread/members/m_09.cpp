#include <iostream>
#include <thread>

void foo()
{
	//...
}

int main()
{
	boolalpha(std::cout);

	std::thread tx{ foo };
	std::cout << "is tx joinable ? : " << (tx.joinable() ? "yes" : "no") << '\n';
	auto ty = move(tx);
	std::cout << "is tx joinable ? : " << (tx.joinable() ? "yes" : "no") << '\n';
	std::cout << "is ty joinable ? : " << (ty.joinable() ? "yes" : "no") << '\n';
	ty.join();
	std::cout << "is ty joinable ? : " << (ty.joinable() ? "yes" : "no") << '\n';

}
