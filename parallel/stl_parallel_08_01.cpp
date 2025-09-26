#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main()
{
    using namespace std;

    vector ivec{ 1, 2, 4, 3, 2, 5, 10 };

    partial_sum(ivec.begin(), ivec.end(), ostream_iterator<int>{cout, " "});
    cout.put('\n');
    partial_sum(ivec.begin(), ivec.end(), ostream_iterator<int>{cout, " "}, multiplies{});
    cout.put('\n');
}
