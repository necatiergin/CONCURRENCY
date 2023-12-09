#include <functional>
#include <iostream>
#include <numeric>
#include <string>

int main()
{
    using namespace std;

    std::vector<string> v1{ "ali", "can", "ece", "ata", "gul", "tan", "eda", "naz" };
    std::vector<string> v2{ "nur", "tan", "ece", "ece", "gul", "tan", "naz", "eda" };
    
    int result = std::inner_product(v1.begin(), v1.end(), v2.begin(), 0, plus{}, equal_to{});
    cout << "result = " << result << '\n';
}
