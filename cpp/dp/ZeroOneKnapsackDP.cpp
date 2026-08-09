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
int knapsackUsingDP(vector<int> &itemWeights, vector<int> &itemValues, int capacity)
{
    int n = itemWeights.size();
    vector<vector<int>> knap(n + 1, vector<int>(capacity + 1));

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= capacity; j++)
        {
            if (i == 0 || j == 0)

                knap[i][j] = 0;
            else
            {
                int pick = 0;
                if (itemWeights.at(i - 1) <= j)
                {
                    pick = itemValues.at(i - 1) + knap[i - 1][j - itemWeights.at(i - 1)];
                }
                int dont_pick = knap[i - 1][j];

                knap[i][j] = std::max(pick, dont_pick);
                std::cout << "Working indexes: " << i << "," << j << " " << ", " << knap[i][j] << std::endl;
            }
        }
    }

    cout << "Value of the last items " << knap[n][capacity] << std::endl;
    return knap[n][capacity];
}

int main()
{
    // int capacity = 50;
    // vector<int> itemWeights = {10, 20, 30};
    // vector<int> itemValues = {60, 100, 120};
    // int result = knapsackUsingDP(wt1, val1, W1, sizeof(wt1) / sizeof(int));

    knapsackUsingDP(wt4, val4, W4);

    return 0;
}