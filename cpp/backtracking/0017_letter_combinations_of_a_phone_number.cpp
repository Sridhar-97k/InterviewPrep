/*
This code is incomplete. Complete it when you have finished backtracking. Park it for now. Dont waste time by visiting it

*/

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iostream>
class Solution
{
public:
    std::map<std::string, std::vector<std::string>> char_map = {
        {"2", {"a", "b", "c"}},
        {"3", {"d", "e", "f"}},
        {"4", {"g", "h", "i"}},
        {"5", {"j", "k", "l"}},
        {"6", {"m", "n", "o"}},
        {"7", {"p", "q", "r", "s"}},
        {"8", {"t", "u", "v"}},
        {"9", {"w", "x", "y", "z"}},
    };

    void getPermRecursion(std::vector<std::string> &result, std::string appended_string, std::string &digits, int first) // we
    {

        if (appended_string.length() == digits.length()) // we insert to the result vector, when we have the exact size, "a" - > "d" -> "g" gives "adg".
        {

            result.push_back(appended_string);
            return;
        }

        std::string first_number = digits.substr(first, 1); // first get for 2::{"a","b","c"}
        std::vector<std::string> alphabetVector = char_map[first_number];

        for (std::vector<std::string>::iterator iter = alphabetVector.begin(); iter != alphabetVector.end(); ++iter)
        {
            std::string stringToAppend = (*iter);
            // std::cout << "This is going to be appended: " << stringToAppend << " to :" << appended_string << std::endl;

            getPermRecursion(result, appended_string + stringToAppend, digits, first + 1);
            // appended_string.pop_back();
            // container.push_back(str+getPermRecursion(container,digits,first+1,last))
        }
    }
    std::vector<std::string> letterCombinations(std::string digits)
    {
        std::vector<std::string> answers;
        if (digits.empty())
            return {};
        getPermRecursion(answers, "", digits, 0);
        return answers;
    }
};

int main()
{
    Solution sol;
    std::vector<std::string> result = sol.letterCombinations("97");
    for (std::string iter_string : result)
    {
        auto it = std::find(result.begin(), result.end(), iter_string);
        std::cout << std::distance(result.begin(), it) << ") " << iter_string << std::endl;
    }
    return 0;
}