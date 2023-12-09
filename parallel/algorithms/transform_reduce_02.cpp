#include <execution>
#include <iostream>
#include <numeric>
#include <vector>


int main()
{
    using namespace std;

    vector<double> target { 0.12, 0.17, 0.25, 0.39, 0.43, 0.70 };
    vector<double> source { 0.08, 0.11, 0.23, 0.36, 0.42, 0.74 };

    auto max_dev = transform_reduce(execution::par,
        target.begin(), target.end(),
        source.begin(),
        0.0,
        [](auto x, auto y) { return max(x, y); },

        // "Transform" operation
        [](auto trg, auto src) { return std::abs(src - trg); }
    );

    cout << "Max devistion is: " << max_dev << '\n';
}
