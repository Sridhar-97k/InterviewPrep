#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
class Solution
{

public:
	int rob(vector<int> &nums)
	{
		return rob_recursion(nums, nums.size() - 1, false, false);
	}

	int rob_recursion(vector<int> &nums, int house, bool prevRobbed, bool firstRobbed)
	{

		if ((house == -1))

			return 0; // no houses left to visit
		int n = nums.size();
		// 		cout<<"Seeing house: "<<house<<" of value: "<<nums[house]<<"
		// which is visited:  "<<visited[house]<<endl;
		if (canRob(house, n, prevRobbed, firstRobbed))

		// if(visited[house-1%visited])
		{
			// 			cout<<"Seeing house: "<<house<<" of value:
			// "<<nums[house]<<" which is visited:  "<<visited[house]<<" canrob:
			// "<<canRob(visited, house)<<endl;
			bool firstAfterTake = (house == n - 1) ? true : firstRobbed;
			int robb = nums[house] + rob_recursion(nums, house - 1, true, firstAfterTake);

			int dont_rob = rob_recursion(nums, house - 1, false, firstRobbed);
			return std::max(robb, dont_rob);
		}
		else
		{

			return rob_recursion(nums, house - 1, false, firstRobbed); // prevrobbed is false because we dont go to the house
		}
	}
	bool canRob(int house, int n, bool prevRobbed, bool firstRobbed)
	{

		if (house == n - 1)
			return true; // this is the case where the first house is checked
		if (house == 0)
			return !prevRobbed && !firstRobbed;
		return !prevRobbed;
	}
};
static std::string toStr(const std::vector<int> &v)
{
	std::string s = "[";
	for (size_t i = 0; i < v.size(); ++i)
	{
		s += std::to_string(v[i]);
		if (i + 1 < v.size())
			s += ",";
	}
	return s + "]";
}

static void runCase(std::vector<int> nums, int expected)
{
	Solution sol;
	auto t0 = std::chrono::steady_clock::now();
	int got = sol.rob(nums);
	auto t1 = std::chrono::steady_clock::now();
	double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();

	std::cout << (got == expected ? "PASS" : "FAIL")
			  << " | input=" << toStr(nums)
			  << " expected=" << expected
			  << " got=" << got
			  << " (" << ms << " ms)\n";
}
int main()
{
	std::ios::sync_with_stdio(false);

	// ---- fixed test cases ----
	runCase({2, 3, 2}, 3);
	runCase({1, 2, 3, 1}, 4);
	runCase({1, 2, 3}, 3);
	runCase({2, 7, 9, 3, 1}, 11);
	runCase({0}, 0);
	runCase({5}, 5);
	runCase({1, 1}, 1);
	runCase({200, 3, 140, 20, 10}, 340);
	runCase({}, 0); // remove if you don't want empty input

	// ---- manual/interactive mode ----
	// Uncomment to feed your own input:
	//   first line: n
	//   second line: n integers
	/*
	int n;
	while (std::cin >> n) {
		std::vector<int> nums(n);
		for (int& x : nums) std::cin >> x;
		Solution sol;
		std::cout << sol.rob(nums) << "\n";
	}
	*/

	return 0;
}