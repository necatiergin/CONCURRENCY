// internal synchronisation

#include <mutex>
#include <list>
#include <syncstream>
#include <iostream>
#include <chrono>

class List {
public:
	void push_back(int x)
	{
		mtx.lock();
		mlist.push_back(x);
		mtx.unlock();
	}

	size_t size() const
	{
		mtx.lock();
		auto ret = mlist.size();
		mtx.unlock();

		return ret;
	}


	void print() const
	{
		mtx.lock();
		std::osyncstream os{ std::cout };

		for (const auto val : mlist)
		{
			os << val << ' ';
		}
		os << '\n';
		mtx.unlock();
	}
	//...
private:
	mutable std::mutex mtx;
	std::list<int> mlist;
};



void foo(List& ls, int val)
{
	using namespace std::literals;

	for (int i = 0; i < 10; ++i) {
		ls.push_back(val + i);
		std::this_thread::sleep_for(50ms);
	}
}

int main()
{
	List mylist;

	{
		std::jthread t1{ foo, std::ref(mylist), 10 };
		std::jthread t2{ foo, std::ref(mylist), 30 };
		std::jthread t3{ foo, std::ref(mylist), 70 };
	}

	mylist.print();
	std::cout << "size = " << mylist.size() << '\n';
}
