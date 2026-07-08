#include <mutex>
#include <thread>
#include <utility>
#include <vector>

class Buffer {
public:
	static constexpr auto size()
	{
		return 16u * 1024u * 1024u;
	}

	Buffer() : m_data(size()) {}

	Buffer(const Buffer&) = delete;
	Buffer& operator=(Buffer&&) = delete;

	void swap(Buffer& other)
	{
		if (this == &other)
			return;

		std::scoped_lock lock(mtx, other.mtx);
		std::swap(m_data, other.m_data);
	}
	// ...
private:
	std::vector<char> m_data;
	mutable std::mutex mtx;
};

Buffer buf_x;
Buffer buf_y;

int main()
{
	std::jthread t1([]() {
		for (long i = 0; i < 1'000'000; ++i)
			buf_x.swap(buf_y);
		});

	std::jthread t2([]() {
		for (long i = 0; i < 1'000'000; ++i)
			buf_y.swap(buf_x); //!!!
		});
}
