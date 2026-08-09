#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

int W1 = 7;
vector<int> wt1 = {1, 3, 4, 5}, val1 = {1, 4, 5, 7}; // 9
int W2 = 10;
vector<int> wt2 = {5, 4, 6, 3}, val2 = {10, 40, 30, 50}; // 90
int W3 = 3;
vector<int> wt3 = {4, 5, 6}, val3 = {10, 20, 30}; // 0
int W4 = 8;
vector<int> wt4 = {3, 3, 2, 5}, val4 = {30, 14, 16, 9}; // 60
int W5 = 50;
vector<int> wt5 = {10, 20, 30}, val5 = {60, 100, 120}; // 220

int knapsackUsingRecursion(vector<int> &wt, vector<int> &val, int capacity, int n)
{
    int take, dont_take;
    // cout << "Capacity is " << capacity << " and im considering the item with weight: " << wt[n - 1] << endl;
    // at each step, we can either take the current weight or not take it, we start with the base case.
    if (n == 0 || capacity == 0)
        return 0;

    if (capacity >= wt[n - 1]) // if the capacity itself is below the weight of the current value
    {

        dont_take = knapsackUsingRecursion(wt, val, capacity, n - 1);
        take = val[n - 1] + knapsackUsingRecursion(wt, val, capacity - wt[n - 1], n - 1);
        // }
        return std::max(take, dont_take);
    }
    else
        return knapsackUsingRecursion(wt, val, capacity, n - 1); // if capacity is less then item weight, dont bother, we have to not-take this item
}
int main()
{

    cout << "Final result is " << knapsackUsingRecursion(wt1, val1, W1, wt1.size()) << endl;
    cout << "Final result is " << knapsackUsingRecursion(wt2, val2, W2, wt2.size()) << endl;
    cout << "Final result is " << knapsackUsingRecursion(wt3, val3, W3, wt3.size()) << endl;
    cout << "Final result is " << knapsackUsingRecursion(wt4, val4, W4, wt4.size()) << endl;
    return 0;
}