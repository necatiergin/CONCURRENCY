#include <iostream>
#include <thread>

class Functor {
public:
	void operator()(int first, int last)const
	{
		for (int i = first; i < last; ++i)
			std::cout << i << ' ';
		
		std::cout << '\n';
	}
};

class Myclass {
public:
	static void sprintn(int first, int last)
	{
		for (int i = first; i < last; ++i)
			std::cout << i << ' ';
		std::cout << '\n';
	}

	void printn(int first, int last) const
	{
		for (int i = first; i < last; ++i)
			std::cout << i << ' ';
		std::cout << '\n';
	}

};

void printn(int first, int last)
{
	for (int i = first; i < last; ++i)
		std::cout << i << ' ';
	std::cout << '\n';
}

int main()
{
	std::thread t1{ printn, 10, 20 };
	t1.join();

	std::thread t2{ Functor{}, 20, 30 };
	t2.join();

	std::thread t3{ [](int first, int last) {
		for (int i = first; i < last; ++i)
			std::cout << i << ' ';
		std::cout << '\n';
	}, 30, 40 };
	t3.join();

	std::thread t4{ Myclass::sprintn, 40, 50 };
	t4.join();

	Myclass m;
	std::thread t5{ &Myclass::printn, m, 50, 60 };
	t5.join();
}
