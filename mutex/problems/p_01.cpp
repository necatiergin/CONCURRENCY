#include <mutex>


class Nec {
	//...
};

class NecWrapper {
public:
	//...
	template <typename F>
	void foo(F func)
	{
		std::lock_guard(mtx);
		func(mnec);
	}

private:
	Nec mnec;
	std::mutex mtx;
};
