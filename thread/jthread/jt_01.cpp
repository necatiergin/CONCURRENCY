//Concurrency in Action kitabında verilen basit bir jthread implementasyonu

#include <thread>


class joining_thread
{
public:
	joining_thread() noexcept = default;

	template<typename Callable, typename ... Args>
	explicit joining_thread(Callable&& func, Args&& ... args) :
		m_t(std::forward<Callable>(func), std::forward<Args>(args)...)
	{}

	explicit joining_thread(std::thread t) noexcept :
		m_t(std::move(t))
	{}

	joining_thread(joining_thread&& other) noexcept :
		m_t(std::move(other.m_t))
	{}

	joining_thread& operator=(joining_thread&& other) noexcept
	{
		if (joinable())
			join();
		m_t = std::move(other.m_t);
		return *this;
	}

	joining_thread& operator=(std::thread other) noexcept
	{
		if (joinable())
			join();
		m_t = std::move(other);
		return *this;
	}

	~joining_thread() noexcept
	{
		if (joinable())
			join();
	}

	void swap(joining_thread& other) noexcept
	{
		m_t.swap(other.m_t);
	}

	std::thread::id get_id() const noexcept
	{
		return m_t.get_id();
	}

	bool joinable() const noexcept
	{
		return m_t.joinable();
	}

	void join()
	{
		m_t.join();
	}

	void detach()
	{
		m_t.detach();
	}

	std::thread& as_thread() noexcept
	{
		return m_t;
	}

	const std::thread& as_thread() const noexcept
	{
		return m_t;
	}
private:
	std::thread m_t;
};
