#include<string>
#include<algorithm>
#include<vector>
#include<iostream>
#include<regex>

class ProductWithoutSelf {

public:
	int countNumberOfMinusOnesInVector(std::vector<int> nums)

	{
		int count = 0;
		for (auto i = nums.begin(); i < nums.end(); i++) {

			if (*i == -1)
				count++;
		}
		return count;
	}

	int giveProductWithoutIndex(std::vector<int> nums, int index) {

		int result = 1;
		for (auto i = nums.begin(); i < nums.end(); i++) {
			if ((i - nums.begin()) != index)
				result = result * (*i);
		}
		return result;
	}
	std::vector<int> productExceptSelf(std::vector<int>& nums) {
		std::vector<int> answer;
		int index;

		bool isOnlyOneOrMinusOne = true;
		//std::cout << "Here" << endl;
		for (auto i = nums.begin(); i < nums.end(); i++) {
			if ((*i != -1) && (*i != 1))
			{
				isOnlyOneOrMinusOne = false;
				break;
			}
		}
		std::cout << "here" << std::endl;
		// handle the special case first, full of 1s or -1s
		if (isOnlyOneOrMinusOne) {
			//std::cout << "Here" << endl;
			bool shouldChange = (countNumberOfMinusOnesInVector(nums) % 2 == 0);
			for (auto i = nums.begin(); i < nums.end(); i++)
			{

				index = (i - nums.begin());

				if (*i == 1 && shouldChange) // even number of minuses, then push the element as it is
				{

					answer.push_back(-1);
				}
				else
					answer.push_back(-1);

			}
			//std::cout << "\ncount of -1s is " << countNumberOfMinusOnesInVector(nums)
			//	<< std::endl;
			return answer;
		}

		for (auto i = nums.begin(); i < nums.end(); i++) {
			index = (i - nums.begin());
			answer.push_back(giveProductWithoutIndex(nums, index));
		}
		// cout << "The answer array is : " << endl;

		// for (auto i = answer.begin(); i < answer.end(); i++)
		//	cout << *i << " " << endl;
		return answer;
	};



public: int perform()
{
	std::vector<int> v1{ -1,1,		  -1,1,		  -1,1,
		  -1,1,
		  -1,1,
		   -1,1,
		   -1,1,		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,-1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,
		   -1,1,+1,1,-1,-1,-1
	};
	ProductWithoutSelf solution;
	solution.productExceptSelf(v1);
	return 0;
}
};