#include <mutex>
#include <vector>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <fstream>
#include <syncstream>

class IStack {
public:
	IStack() {};
	IStack(const IStack&) = delete;
	IStack& operator=(const IStack&) = delete;

	int pop()
	{
		std::unique_lock lock(mtx);
		m_cv.wait(lock, [this]() {return !m_vec.empty(); });
		int val = m_vec.back();
		m_vec.pop_back();
		return val;
	}

	void push(int x)
	{
		std::scoped_lock lock(mtx);
		m_vec.push_back(x);
		m_cv.notify_one();
	}
private:
	std::vector<int> m_vec;
	mutable std::mutex mtx;
	mutable std::condition_variable m_cv;
};

constexpr int n{ 1'000 };
IStack gstack;

void producer(std::ofstream& ofs)
{
	for (int i = 0; i < n; ++i) {
		gstack.push(2 * i + 1);
		std::osyncstream{ ofs} << 2 * i + 1 << " pushed\n";
	}
}

void consumer(std::ofstream& ofs)
{
	for (int i = 0; i < n; ++i) {
		std::osyncstream{ ofs } << gstack.pop() << " popped\n";
	}
}

int main()
{
	std::ofstream ofs{ "log.txt" };
	if (!ofs) {
		std::cerr << "cannot create log.txt\n";
		exit(EXIT_FAILURE);
	}

	std::jthread th1(producer, std::ref(ofs));
	std::jthread th2(consumer, std::ref(ofs));
}
