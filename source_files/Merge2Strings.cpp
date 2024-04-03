#include<string>
#include<iostream>
using namespace std;
class Merge2Strings {
public:
	string mergeAlternately(string word1, string word2)
	{
		std::cout << "First word is " << word1 << std::endl;
		std::cout << "Second word is " << word2 << std::endl;
		string result = "";
		int i = 0, j = 0;
		for (;;)
		{
			if (((i + j) % 2 == 0)) 
			{
				if (i < word1.length()) {
					result = result + word1.at(i);
					std::cout << "The alphabet is " << word1.at(i) << std::endl;
					i++;
				}
				else break;

			}
			if (((i + j) % 2 == 1)) 
			{
				if (j < word2.length()) {
					result = result + word2.at(j);
					std::cout << "The alphabet is " << word2.at(j) << std::endl;
					j++;
				}
				else break;

			}
		}
		

		/// now add all the remaining elements in the first word

		for (int a = i; a < word1.length(); a++)
		{
			result = result + word1.at(a);
		}

		// now add all the remaining elements in the second word
		for (int b = j; b < word2.length(); b++)
		{
			result = result + word2.at(b);
		}
		std::cout << "The value of final result now is " << result << std::endl;
		return result;

	}
public:  int perform()
{
	Merge2Strings solution;
	solution.mergeAlternately("abc", "pqrstu");
	return 0;
}


};

