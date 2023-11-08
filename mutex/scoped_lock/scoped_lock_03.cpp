#include <mutex>
#include <iostream>
#include <vector>


class Buffer {
public:
	Buffer(char c) : cvec(100, c) {}
	void print() const
	{
		for (char c : cvec)
			std::cout << c;
		std::cout << std::endl;
	}

	//alternatif kod (scoped_lock dile eklenmeden önce
	/*
	void swap(Buffer& other)
	{
		std::lock(mtx, other.mtx);
		std::lock_guard guard1{ mtx, std::adopt_lock };
		std::lock_guard guard2{ other.mtx, std::adopt_lock };
		std::swap(cvec, other.cvec);
	}
	*/

	void swap(Buffer& other)
	{
		std::scoped_lock guard{ mtx, other.mtx };
		std::swap(cvec, other.cvec);
	}

private:
	std::vector<char> cvec;
	std::mutex mtx;
};

Buffer bx{ 'A' };
Buffer by{ 'X' };

int main()
{
	using namespace std;

	bx.print();
	by.print();

	thread t1{ [] {
		for (int i = 0; i < 10; ++i)
			bx.swap(by);
		} };

	thread t2{ [] {
		for (int i = 0; i < 9; ++i)
			by.swap(bx);
		} };

	t1.join();
	t2.join();
	std::cout << "\n\n";

	bx.print();
	by.print();

}
