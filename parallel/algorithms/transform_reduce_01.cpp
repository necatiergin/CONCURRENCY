#include <iostream>
#include <numeric>
#include <vector>
#include <functional>
#include <execution>

int main()
{
    std::vector<int> x{ 2, 3, 1, 5, 6 };
    std::vector<int> y{ 1, 2, 4, 3, 5 };
    //                  2  6  4  15 30

    auto result = std::transform_reduce(std::execution::par, x.begin(), x.end(), y.begin(), 0);
    std::cout << "Inner product of x and y: " << result << '\n';
}
