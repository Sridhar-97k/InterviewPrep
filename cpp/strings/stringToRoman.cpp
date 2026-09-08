#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cmath>

class Solution
{
public:
    // std::map<int, std::string> char_map = {};
    std::string answer;
    int getFirstDigit(int num)
    {
        if (num >= 1000)
            return num / 1000;
        if (num >= 100)
            return num / 100;
        if (num >= 10)
            return num / 10;

        return num;
    }
    std::string intToRoman(int num)
    {
        // std::vector<int> digits;

        // char_map.insert({1, "M"});
        // char_map.insert({5, "V"});
        // char_map.insert({10, "X"});
        // char_map.insert({50, "L"});
        // char_map.insert({100, "C"});

        // char_map.insert({500, "D"});
        // char_map.insert({1000, "M"});

        // std::reverse(digits.begin(), digits.end());
        // std::cout << "The power is : " << --power << std::endl;

        int actual_value = num;

        for (;;)
        {
            // counter++;
            if (actual_value <= 0)
                break;
            int digit = getFirstDigit(actual_value);
            // std::cout << " The digit is " << digit << std::endl;
            // if power has gone down, then we need to decremen

            if (digit != 4 && digit != 9)
            {
                if (actual_value >= 1000)
                {

                    actual_value = actual_value - 1000;
                    answer.append("M");
                }
                else if (actual_value >= 500)
                {

                    actual_value = actual_value - 500;
                    answer.append("D");
                }
                else if (actual_value >= 100)
                {

                    actual_value = actual_value - 100;
                    answer.append("C");
                }
                else if (actual_value >= 50)
                {

                    actual_value = actual_value - 50;
                    answer.append("L");
                }
                else if (actual_value >= 10)
                {

                    actual_value = actual_value - 10;
                    answer.append("X");
                }
                else if (actual_value >= 5)
                {

                    actual_value = actual_value - 5;
                    answer.append("V");
                }
                else
                {
                    if (actual_value == 3)
                    {
                        actual_value = actual_value - 3;
                        answer.append("III");
                    }
                    else if (actual_value == 2)
                    {
                        actual_value = actual_value - 2;
                        answer.append("II");
                    }
                    else if (actual_value == 1)
                    {
                        actual_value = actual_value - 1;
                        answer.append("I");
                    }
                }
            }
            else if (digit == 4)
            {

                if (actual_value >= 400)
                {

                    actual_value = actual_value - 400;
                    answer.append("CD");
                }
                else if (actual_value >= 40)
                {

                    actual_value = actual_value - 40;
                    answer.append("XL");
                }
                else
                {

                    actual_value = actual_value - 4;
                    answer.append("IV");
                }
            }
            else if (digit == 9)
            {

                if (actual_value >= 900)
                {

                    actual_value = actual_value - 900;
                    answer.append("CM");
                }
                else if (actual_value >= 90)
                {

                    actual_value = actual_value - 90;
                    answer.append("XC");
                }
                else
                {

                    actual_value = actual_value - 9;
                    answer.append("IX");
                }
            }
        }
        return answer;
    }
};
int main()
{
    Solution sol;
    std::cout << sol.intToRoman(5) << std::endl;

    return 0;
}