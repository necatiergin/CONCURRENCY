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
    cout << accumulate(ivec.begin(), ivec.end(), 0, 
        [](int prev_result, int val) { 
            return prev_result + val; })
        << '\n';
    
    auto fn = [](string prev_result, int val) { return prev_result + '-' + to_string(val); };

    cout << accumulate(ivec.begin(), ivec.end(), ""s, fn) << '\n';
    cout << reduce(execution::par, ivec.begin(), ivec.end(), ""s, fn) << '\n'; //??
}
