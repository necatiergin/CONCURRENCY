#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <future>
#include <iomanip>

std::map<char, size_t> histogram(const std::string& str)
{
	std::map<char, size_t> cmap{};
	for (const auto c : str)
	{
		++cmap[c];
	}

	return cmap;
}

std::string get_sorted(std::string str)
{
	sort(str.begin(), str.end());
	erase_if(str, [](const char c) {return isspace(c);});
	//str.erase(remove(str.begin(), str.end(), ' '),str.end()); //Remove erase idiom
	return str;
}


bool is_vowel(char c)
{
	std::string str{ "aeiouAEIOU" };
	return find(str.begin(), str.end(), c) != str.end();
}

size_t count_vowel(const std::string& str)
{
	return count_if(str.begin(), str.end(), is_vowel);

}

int main()
{
	
	std::string sline;
	std::cout << "Enter a string : ";
	getline(std::cin, sline);

	auto hist = std::async(histogram,sline);
	auto sorted_string = std::async(get_sorted,sline);
	auto vowel_cnt = std::async(count_vowel,sline);
	
	for (const auto& [c, count] : hist.get())
	{
		std::cout << c << ' ' << count << '\n';
	}

	std::cout << "sorted string : "
		<< quoted(sorted_string.get()) << '\n'
		<< "total vowels : "
		<< vowel_cnt.get() << '\n';

}
