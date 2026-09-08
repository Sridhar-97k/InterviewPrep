#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

class ReverseStringUsingRecursion {

	void reverseUsingRecursion(string input_string)
	{
		if (input_string.length() == 0)
			return;
		string newString = input_string.substr(1, input_string.length() - 1);
		cout << "nThe new string is : " << newString << endl;
		reverseUsingRecursion(newString);

		std::cout << input_string.at(0);
	
	}

public: int perform()
	{
		string string1 = "HelloWorld";

		std::cout << "The reverse of " << string1 << " is ";
		reverseUsingRecursion(string1);
	
		return 0;
	}
	

};

int main() {
	ReverseStringUsingRecursion solution;
	solution.perform();
	return 0;
}
