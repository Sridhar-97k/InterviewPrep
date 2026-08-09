/*
This code is incomplete. Complete it when you have finished backtracking

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
    void getPermRecursion(std::vector<std::string> &container, std::string &digits, int first, int last)
    {

        if (first == last)

            return;

        std::string this_string = digits.substr(first, 1); // first get for 2::{"a","b","c"}
        std::vector<std::string> alphabetVector = char_map[this_string];
        std::vector<std::string>::iterator iter;
        ;

        for (iter = alphabetVector.begin(); iter != alphabetVector.end(); ++iter)
        {
            std::string str = *iter;
            // container.push_back(str+getPermRecursion(container,digits,first+1,last))
        }
    }

    std::vector<std::string> letterCombinations(std::string digits)
    {
        // std::vector<std::string> answers;
        // std::vector<std::string> chars;
        std::vector<std::string> answers;
        getPermRecursion(answers, digits, 0, digits.length());
        return {""};
    }
};

int main()
{
    Solution sol;
    sol.letterCombinations("2");
    return 0;
}