#include <vector>
#include <iostream>
using namespace std;

// LeetCode 4 - Median of Two Sorted Arrays.
// Simple O(m+n) merge approach (not the optimal O(log(m+n)) binary search,
// but correct and easy to reason about).
class MedianSortedArrays {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
	{
		vector<int> merged;
		merged.reserve(nums1.size() + nums2.size());

		size_t i = 0, j = 0;
		while (i < nums1.size() && j < nums2.size())
			merged.push_back(nums1[i] <= nums2[j] ? nums1[i++] : nums2[j++]);
		while (i < nums1.size()) merged.push_back(nums1[i++]);
		while (j < nums2.size()) merged.push_back(nums2[j++]);

		size_t n = merged.size();
		if (n == 0) return 0.0;
		if (n % 2 == 1) return merged[n / 2];
		return (merged[n / 2 - 1] + merged[n / 2]) / 2.0;
	}

	int perform()
	{
		vector<int> a{ 1, 3 };
		vector<int> b{ 2 };
		cout << "Median: " << findMedianSortedArrays(a, b) << endl; // 2
		return 0;
	}
};

int main()
{
	MedianSortedArrays solution;
	solution.perform();
	return 0;
}
