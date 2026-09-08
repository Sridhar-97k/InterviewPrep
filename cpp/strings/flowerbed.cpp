#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

class Flowerbed
{

public:
	bool canPlaceFlowers(std::vector<int> &flowerbed, int n)
	{

		int size = flowerbed.size();
		int counter = 0;
		for (int i = 0; i < size; i++)
		{

			bool leftPlace = i == 0 || flowerbed[i - 1] == 0;
			bool rightPlace = i == (size - 1) || flowerbed[i + 1] == 0;

			if (flowerbed[i] == 0 && leftPlace && rightPlace)
			{
				flowerbed[i] = 1;
				counter++;
			}
		}

		return counter >= n;
	}

	int perform()
	{
		std::vector<int> flowerbed = {1, 0, 0, 0, 0, 1};
		bool result = canPlaceFlowers(flowerbed, 2);
		std::cout << std::boolalpha << "Can place: " << result << std::endl;
		return 0;
	}
};

int main()
{
	Flowerbed solution;
	solution.perform();
	return 0;
}
