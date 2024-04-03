#include<string>
#include<algorithm>
#include<vector>
#include<iostream>


class ReverseVowelsInArray {
public:
	bool isVowel(char s)
	{
		if (s == 'a' || s == 'e' || s == 'i' || s == 'o' || s == 'u')
			return true;
		if (s == 'A' || s == 'E' || s == 'I' || s == 'O' || s == 'U')
			return true;
		return false;
	}
	std::string reverseVowels(std::string s) {

		//char* characters = new char[s.length()];
		std::vector<char> vowels;

		for (int x = 0; x < s.length(); x++)
		{
			//characters[x] = s.at(x);
			if (isVowel(s.at(x)))
			{
				//cout << "Value is " << characters[x] << endl;
				vowels.push_back(s.at(x));
			}
		}
		for (int i = 0; i < vowels.size() / 2; i++)
		{

			//cout << vowels[i] << " " << endl;
			std::swap(vowels[i], vowels[vowels.size() - (i + 1)]);
		}
		reverse(vowels.begin(), vowels.end());
		std::cout << "After changing";
		for (int i = 0; i < vowels.size(); i++)
		{
			std::cout << vowels[i] << ",";
			//vowels[i] = vowels[vowels.size() - 1]; // reversing the vowel position
		}
		std::cout << std::endl;
		int i = 0;
		for (int x = 0; x < s.length(); x++)
		{

			if (isVowel(s.at(x)))
			{
				//characters[x] = vowels[i++];
				s[x] = vowels[i++];
			}
		}
		//characters[s.length()] = '\0';

		return s;

	};


public: int perform()
{
	ReverseVowelsInArray solution;
	solution.reverseVowels("aaaai");

	return 0;
}
};