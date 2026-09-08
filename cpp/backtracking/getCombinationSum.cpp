#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
class Solution
{
    vector<vector<int>> result;

public:
    void getCombination(vector<int> &candidates, vector<int> &numbers, int target, int sum, int start)
    {
        if (sum > target)
            return;
        if (sum == target)
        {
            result.push_back(numbers);
            // // cout << "The numbers are " << endl;
            // for (auto i = numbers.begin(); i != numbers.end(); i++)
            // {
            //     cout << (*i) << " ";
            // }
            // cout << endl;
            return;
        }
        for (int i = start; i < (int)candidates.size(); i++)
        {
            // cout << "Now checking " << candidates[i] << endl;
            numbers.push_back(candidates.at(i));
            getCombination(candidates, numbers, target, sum + candidates.at(i), i);
            numbers.pop_back();
            // considering
        }
    }

    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {

        vector<int> nums = {};
        std::sort(candidates.begin(), candidates.end());
        getCombination(candidates, nums, target, 0, 0);

        return result;
    }
};

int main()
{
    Solution sol;
    std::vector<int> candidates = {2, 3, 6, 7};
    int target = 7;
    vector<vector<int>> returnValue = sol.combinationSum(candidates, target);
    for (auto i = returnValue.begin(); i != returnValue.end(); ++i)
    {
        cout << "One set of number is " << endl;
        for (auto j = (*i).begin(); j != (*i).end(); ++j)
            cout << (*j) << " ";
        cout << endl;
    }
}