#include <functional>
#include <future>
#include <iostream>
#include <syncstream>
#include <utility>
#include <vector>

using ipair = std::pair<int, int>;

void func(std::packaged_task<int(int, int)>& ptask, const std::vector<ipair>& pairs)
{
	std::osyncstream os{ std::cout };
	for (auto [x, y] : pairs) {
		auto ftr = ptask.get_future();
		ptask(x, y);
		os << x << " * " << x << " + " << y << " * " << y << " = " << ftr.get() << '\n';
		ptask.reset();
	}
}


int main()
{
	std::vector<ipair> pvec;

	pvec.emplace_back(1, 3);
	pvec.emplace_back(3, 5);
	pvec.emplace_back(7, 9);
	pvec.emplace_back(11, 13);
	pvec.emplace_back(15, 17);

	std::packaged_task<int(int, int)> pt{ [](int x, int y)
		{
			return x * x + y * y;
		}
	};

	std::jthread t(func, std::ref(pt), pvec);
	func(pt, pvec);

	
}
