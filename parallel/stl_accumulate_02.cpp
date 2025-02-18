#include <vector>
#include <numeric>
#include <iostream>
#include <string>
#include <execution>

int main()
{
    using namespace std;

    vector<int> ivec{ 1, 3, 5, 7, 9 };

    cout << accumulate(ivec.begin(), ivec.end(), 0) << '\n';
    cout << accumulate(ivec.begin(), ivec.end(), 0, [](int prev_result, int val) { return prev_result + val; }) << '\n';
    cout << accumulate(ivec.begin(), ivec.end(), ""s, [](string prev_result, int val) { return prev_result + '-' + to_string(val); }) << '\n';
    //cout << reduce(execution::par, ivec.begin(), ivec.end(), "0"s, [](string prev_result, int val) { return prev_result + to_string(val); }) << '\n';
}
