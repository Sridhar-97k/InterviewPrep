#include<vector>
#include<iostream>
using namespace std;

class VectorMergeSortedArray {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		int i = 0, j = 0;
		if (m == 0) {
			nums1.resize(m, n);
			for (int i = 0; i < nums2.size(); i++)
				nums1.push_back(nums2[i]);
			return;
		}
		i = 0, j = 0;
		if (n != 0) {
			// nums1.resize(m,m+n);
			vector<int> temp;
			for (int x = 0; x < (m + n);) {

				bool value = nums1[i] <= nums2[j];
				if ((i < m) && value) {
					// cout << "pushing back first array element" <<nums1[i]<< endl;
					temp.push_back(nums1[i++]);
					x++;

				}

				else if ((j < n)) {
					//cout << "pushing back second array element"<<nums2[j]<< endl;
					temp.push_back(nums2[j++]);
					x++;

				}
			}

			nums1.clear();

			for (int i = 0; i < temp.size(); i++)
				nums1.push_back(temp[i]);
		}
	}





public: int perform()
{
	vector <int> m1;
	vector<int>m2;
	VectorMergeSortedArray solution;
	m1.push_back(1);
	m1.push_back(2);
	m1.push_back(3);
	m1.push_back(0);
	m1.push_back(0);
	m1.push_back(0);

	m2.push_back(2);
	m2.push_back(5);
	m2.push_back(6);
	solution.merge(m1, 3, m2, 3);
	return 0;

}
};