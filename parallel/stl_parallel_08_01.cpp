#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main()
{
    using namespace std;

    vector svec{ 1, 2, 4, 3, 2, 5, 10 };
    
    partial_sum(svec.begin(), svec.end(), ostream_iterator<int>{cout, " "});
    cout.put('\n');
    partial_sum(svec.begin(), svec.end(), ostream_iterator<int>{cout, " "}, multiplies{});
    cout.put('\n');
}
