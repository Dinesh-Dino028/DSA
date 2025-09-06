#include <bits/stdc++.h>
using namespace std;

class TwoPointerArray
{
public:
    bool twoSum(vector<int> &arr, int target)
    {
        int n = arr.size();
        int left = 0, right = n - 1;
        sort(arr.begin(), arr.end());

        while (left < right)
        {
            int sum = arr[left] + arr[right];
            if (sum == target)
            {
                return true;
            }
            else if (sum < target)
            {
                left++;
            }
            else
            {
                right--;
            }
        }
        return false;
    }

    bool findTriplets(vector<int> &arr)
    {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        for (int i = 0; i < n; i++)
        {
            int left = i + 1;
            int right = n - 1;
            while (left < right)
            {
                int sum = arr[i] + arr[left] + arr[right];
                if (sum == 0)
                {
                    return true;
                }
                else if (sum < 0)
                {
                    left++;
                }
                else
                {
                    right--;
                }
            }
        }

        return false;
    }

    int countTriplet(vector<int> &arr)
    {
        int n = arr.size();
        int count = 0;
        sort(arr.begin(), arr.end());
        for (int k = n - 1; k >= 2; k--)
        {
            int i = 0;
            int j = k - 1;
            while (i < j)
            {
                int sum = arr[i] + arr[j];
                if (sum == arr[k])
                {
                    count++;
                    i++;
                    j--;
                }
                else if (sum < arr[k])
                {
                    i++;
                }
                else
                {
                    j--;
                }
            }
        }
        return count;
    }

    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        int n = nums.size();
        vector<vector<int>> result;
        if (n < 4)
            return result;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 3; i++)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            for (int j = i + 1; j < n - 2; j++)
            {
                if (j > i + 1 && nums[j] == nums[j - 1])
                    continue;

                int left = j + 1;
                int right = n - 1;

                while (left < right)
                {
                    long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];

                    if (sum == target)
                    {
                        result.push_back({nums[i], nums[j], nums[left], nums[right]});

                        while (left < right && nums[left] == nums[left + 1])
                            left++;
                        while (left < right && nums[right] == nums[right - 1])
                            right--;

                        left++;
                        right--;
                    }
                    else if (sum < target)
                    {
                        left++;
                    }
                    else
                    {
                        right--;
                    }
                }
            }
        }
        return result;
    }

    int findUnionCount(vector<int> &a, vector<int> &b)
    {
        set<int> unionCount;
        for (int i = 0; i < a.size(); i++)
        {
            unionCount.insert(a[i]);
        }
        for (int i = 0; i < b.size(); i++)
        {
            unionCount.insert(b[i]);
        }
        return unionCount.size();
    }

    vector<int> findUnion(vector<int> &a, vector<int> &b)
    {
        set<int> unionCount;
        vector<int> result;
        for (int i = 0; i < a.size(); i++)
        {
            unionCount.insert(a[i]);
        }
        for (int i = 0; i < b.size(); i++)
        {
            unionCount.insert(b[i]);
        }
        result.insert(result.end(), unionCount.begin(), unionCount.end());
        return result;
    }

    int numberofElementsInIntersection(vector<int> &a, vector<int> &b)
    {
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        int i = 0, j = 0, count = 0;

        while (i < a.size() && j < b.size())
        {
            if (a[i] == b[j])
            {
                count++;
                int val = a[i];
                // Skip duplicates
                while (i < a.size() && a[i] == val)
                    i++;
                while (j < b.size() && b[j] == val)
                    j++;
            }
            else if (a[i] < b[j])
            {
                i++;
            }
            else
            {
                j++;
            }
        }
        return count;
    }

    vector<int> removeDuplicates(vector<int> &arr)
    {
        // code here
        int n = arr.size();
        if (n < 1)
        {
            return arr;
        }
        sort(arr.begin(), arr.end());
        int index = 0;
        vector<int> ans;
        ans.push_back(arr[0]);
        for (int i = 1; i < n; i++)
        {
            if (arr[i] != arr[i - 1])
            {
                ans.push_back(arr[i]);
            }
        }
        return ans;
    }

    int removeDuplicates2(vector<int> &arr)
    {
        if (arr.empty())
            return 0; // Edge case: empty array

        int index = 0; // Pointer for the position of unique elements

        // Traverse the array and keep only distinct elements
        for (int i = 1; i < arr.size(); i++)
        {
            if (arr[i] != arr[index])
            { // If a new distinct element is found
                index++;
                arr[index] = arr[i]; // Move distinct element forward
            }
        }

        return index + 1; // Return the size of the modified array
    }

    int kthElement(vector<int> &a, vector<int> &b, int k)
    {
        int i = 0, j = 0, count = 0;
        int ans = -1;

        while (i < a.size() && j < b.size())
        {
            if (a[i] < b[j])
            {
                ans = a[i];
                i++;
            }
            else
            {
                ans = b[j];
                j++;
            }
            count++;
            if (count == k)
                return ans;
        }

        // If elements left in a[]
        while (i < a.size())
        {
            ans = a[i];
            i++;
            count++;
            if (count == k)
                return ans;
        }

        // If elements left in b[]
        while (j < b.size())
        {
            ans = b[j];
            j++;
            count++;
            if (count == k)
                return ans;
        }

        return -1; // if k is out of bounds
    }

    int longestSubarray(vector<int> &arr, int k)
    {
        unordered_map<int, int> prefixIndex;
        int sum = 0, maxLen = 0;

        for (int i = 0; i < arr.size(); i++)
        {
            sum += arr[i];

            if (sum == k)
            {
                maxLen = i + 1;
            }

            if (prefixIndex.find(sum - k) != prefixIndex.end())
            {
                maxLen = max(maxLen, i - prefixIndex[sum - k]);
            }

            if (prefixIndex.find(sum) == prefixIndex.end())
            {
                prefixIndex[sum] = i;
            }
        }
        return maxLen;
    }

    int maxWater(vector<int> &arr)
    {
        int n = arr.size();
        int left = 0, right = n - 1;
        int res = 0;
        int maxLeft = 0, maxRight = 0;

        while (left <= right)
        {
            if (arr[left] <= arr[right])
            {
                if (arr[left] >= maxLeft)
                {
                    maxLeft = arr[left];
                }
                else
                {
                    res += maxLeft - arr[left];
                }
                left++;
            }
            else
            {
                if (arr[right] >= maxRight)
                {
                    maxRight = arr[right];
                }
                else
                {
                    res += maxRight - arr[right];
                }
                right--;
            }
        }
        return res;
    }

    int majorityElement(vector<int> &nums)
    {

        // two pointer approach
        int candidate = nums[0];
        int count = 0;

        for (auto num : nums)
        {
            if (count == 0)
            {
                candidate = num;
                count++;
            }
            else if (num == candidate)
            {
                count++;
            }
            else
            {
                count--;
            }
        }
        return candidate;

        // optimal
        //  int n = nums.size();
        //  int m = n / 2;
        //  int res = 0;
        //  unordered_map<int, int> map;
        //  for (int i = 0; i < n; i++)
        //  {
        //      map[nums[i]]++;
        //      if (map[nums[i]] > m)
        //      {
        //          res = nums[i];
        //          break;
        //      }
        //  }
        //  return res;
    }

    int maxSubarraySum(vector<int> &arr) // kadane's Algo
    {
        int currSum = arr[0];
        int maxSum = arr[0];

        for (int i = 1; i < arr.size(); i++)
        {
            currSum = max(arr[i], currSum + arr[i]); // extend / restart
            maxSum = max(currSum, maxSum); // update answer
        }

        return maxSum;
    }

    int inversionCount(vector<int> &arr)
    {
        // Your Code Here
        int count = 0;
        for (int i = 0; i <= arr.size() - 1; i++)
        {
            for (int j = i; j <= arr.size() - 1; j++)
            {
                if (arr[i] > arr[j])
                {
                    count++;
                }
            }
        }
        return count;
    }

    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        vector<vector<int>> res;
        int n = intervals.size();
        sort(intervals.begin(), intervals.end());
        for (int i = 0; i < n; i++)
        {
            if (res.empty() || intervals[i][0] > res.back()[1])
            {
                res.push_back(intervals[i]);
            }
            else
            {
                res.back()[1] = max(res.back()[1], intervals[i][1]);
            }
        }
        return res;
    }

    int maxProduct(vector<int> &arr)
    {
        int prefix = 1, suffix = 1;
        int ans = INT_MIN;
        int n = arr.size();
        for (int i = 0; i < n; i++)
        {
            if (prefix == 0)
            {
                prefix = 1;
            }
            if (suffix == 0)
            {
                suffix = 1;
            }
            prefix = prefix * arr[i];
            suffix = suffix * arr[n - i - 1];
            ans = max(ans, max(prefix, suffix));
        }
        return ans;
    }

    void nextPermutation(vector<int> &nums)
    {
        int n = nums.size();
        int i = n - 2;

        // Step 1: Find the pivot
        while (i >= 0 && nums[i] >= nums[i + 1])
        {
            i--;
        }

        if (i >= 0)
        {
            // Step 2: Find the next greater element and swap
            int j = n - 1;
            while (nums[j] <= nums[i])
            {
                j--;
            }
            swap(nums[i], nums[j]);
        }

        // Step 3: Reverse the suffix
        reverse(nums.begin() + i + 1, nums.end());
    }
};

int main()
{
    TwoPointerArray tpa;
    vector<int> arr = {1, 2, 3};
    vector<int> arr2 = {89, 2, 4};
    // auto ans =
    tpa.nextPermutation(arr);
    // cout << ans;
    for (auto a : arr)
    {
        cout << a << " ";
    }
    // for (auto a : ans)
    // {
    //     for (auto b : a)
    //     {
    //         cout << b << " ";
    //     }
    //     cout << endl;
    // }
    return 0;
}