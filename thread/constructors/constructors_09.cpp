#include <iostream>
#include <thread>

class Functor {
public:
	void operator()(int x) const
	{
		std::cout << "x = " << x << '\n';
	}
};

int main()
{
	Functor f;

	std::thread tx{f, 12}; //valid
	
	tx.join();
}
