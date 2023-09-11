#include <iostream>
#include <thread>

class Functor {
public:
	void operator()(int n)const
	{
		for (int i = 0; i < n; ++i)
			std::cout << i << " ";
		std::cout << std::endl;
	}
};

class Myclass {
public:
	static void sprintn(int n)
	{
		for (int i = 0; i < n; ++i)
			std::cout << i << ' ';
		std::cout << '\n';
	}

	void printn(int n)const
	{
		for (int i = 0; i < n; ++i)
			std::cout << i << ' ';
		std::cout << '\n';
	}

};

void printn(int n)
{
	for (int i = 0; i < n; ++i)
		std::cout << i << ' ';
	std::cout << '\n';
}

int main()
{
	std::thread t1{ printn, 10 };
	t1.join();
	
	std::thread t2{ Functor{}, 10 };
	t2.join();

	std::thread t3{ [](int n) {
		for (int i = 0; i < n; ++i)
			std::cout << i << ' ';
		std::cout << std::endl;
	}, 10};
	t3.join();

	std::thread t4{ Myclass::sprintn, 10 };
	t4.join();

	Myclass m;
	std::thread t5{ &Myclass::printn, m, 10 };
	t5.join();
}
