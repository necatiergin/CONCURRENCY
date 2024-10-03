#include <thread>
#include <iostream>
#include <functional>

class Nec {
public:
	Nec(int x) : mx{x} {}
	void set(int x) { mx = x; }
	void print()const
	{
		std::cout << "(" << mx << ")\n";
	}
private:
	int mx;
};

int main()
{
	Nec mynec{ 15 };
	mynec.print();

	std::thread th1{ &Nec::set, mynec, 42 };
	th1.join();
	mynec.print();
	std::thread th2{ &Nec::set, &mynec, 42 };
	th2.join();
	mynec.print();
	std::thread th3{ &Nec::set, std::ref(mynec), 99};
	th3.join();
	mynec.print();
}
