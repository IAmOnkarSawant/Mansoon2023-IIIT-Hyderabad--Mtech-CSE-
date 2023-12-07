#include <iostream>
using namespace std;

void assignRanks(int nums[], int n, int ranks[])
{
    int sorted_nums[n];
    for (int i = 0; i < n; i++)
    {
        sorted_nums[i] = nums[i];
    }

    for (int i = 0; i < n; i++)
    {
        ranks[i] = 1;
        for (int j = 0; j < n; j++)
        {
            if (nums[i] > sorted_nums[j])
            {
                ranks[i]++;
            }
        }
    }
}

int solve(int nums[], int n)
{
    if (n == 0)
        return 0;

    int lengths[n];
    int counts[n];
    int ranks[n];

    assignRanks(nums, n, ranks);

    for (int i = 0; i < n; ++i)
    {
        lengths[i] = 1;
        counts[i] = 1;
    }

    int max_length = 1;
    int result = 1;

    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (ranks[i] > ranks[j])
            {
                if (lengths[i] == lengths[j] + 1)
                {
                    counts[i] += counts[j];
                }
                else if (lengths[i] < lengths[j] + 1)
                {
                    lengths[i] = lengths[j] + 1;
                    counts[i] = counts[j];
                }
            }
        }

        if (lengths[i] == max_length)
        {
            result += counts[i];
        }
        else if (lengths[i] > max_length)
        {
            max_length = lengths[i];
            result = counts[i];
        }
    }

    return result;
}

int main()
{
    int n;
    cin >> n;

    int nums[n];
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    cout << solve(nums, n) << endl;
    return 0;
}