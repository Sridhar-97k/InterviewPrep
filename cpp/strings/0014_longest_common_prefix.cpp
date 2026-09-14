#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution
{
public:
    string longestCommonPrefix(vector<string> &strs)
    {
        if (strs.empty())
            return "";
        auto shortest_it = std::min_element(strs.begin(), strs.end(),
                                            [](const std::string &a, const std::string &b)
                                            {
                                                return a.size() < b.size();
                                            });

        // Get the length of that string
        size_t shortest_length = shortest_it->size();
        string prefix = "";

        // for (int i = 0; i < strs.size(); i++) { // going through eacd string
        int k = 0;
        for (int j = 0; j < shortest_length; j++)
        {

            for (k = 0; k < strs.size(); k++)
            {
                // cout << "Character is " << strs[k][j] << endl;
                if (k >= 1 && (strs[k][j] != strs[k - 1][j]))
                    return prefix;
            }
            // cout << "Character now is " << strs[k - 1][j] << endl;
            prefix = prefix + strs[k - 1][j];
            // cout << "Prefix now is " << prefix << endl;
        }
        cout << "Prefix now is " << prefix << endl;
        return prefix;
    }
};

int main()
{
    Solution sol;
    vector<string> strings;
    strings.push_back("flower");
    strings.push_back("flow");
    strings.push_back("float");
    sol.longestCommonPrefix(strings);
}