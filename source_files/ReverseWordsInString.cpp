#include<string>
#include<algorithm>
#include<vector>
#include<iostream>
#include<regex>

class ReverseWordsInString {
public:

	std::string reverseWords(std::string s) {
		std::vector<std::string> words;
		std::regex rgx("\\s+");
		std::sregex_token_iterator iter(s.begin(),
			s.end(),
			rgx,
			-1);
		std::sregex_token_iterator end;
		for (; iter != end; ++iter) {
			//std::cout << *iter << '\n';
			std::string str = (*iter);
			if (!str.empty())
				words.push_back(*iter);
		}
		// words.erase(words.end()-1);
		reverse(words.begin(), words.end());
		//cout << "reversal done";
		std::string returnString;

		for (auto i = words.begin(); i < words.end(); i++)
		{
			returnString = returnString + *i + " ";
		}


		return  returnString = returnString.substr(0, returnString.size() - 1);

	};


public : int perform()
	{
		ReverseWordsInString solution;
		std::cout << "\"" << solution.reverseWords(" a good   example") << "\"" << std::endl;
		return 0;
	}
};