#include <bits/stdc++.h>
#include <chrono>
#include <cmath>
using namespace std;

class Arrays
{
public:
    pair<int, int> getMinMax(vector<int> arr)
    {
        int minElement = arr[0];
        int maxElement = arr[0];
        if (arr.size() == 0)
        {
            return {arr[0], arr[0]};
        }
        for (int num : arr)
        {
            if (num < minElement)
            {
                minElement = num;
            }
            if (num > maxElement)
            {
                maxElement = num;
            }
        }

        return {minElement, maxElement};
    }

    int thirdLargest(vector<int> &arr)
    {
        if (arr.size() < 3)
        {
            return -1;
        }

        sort(arr.begin(), arr.end(), greater<int>());

        int count = 1;
        int prev = arr[0];

        for (int i = 1; i < arr.size(); i++)
        {
            if (arr[i] != prev)
            {
                count++;
                prev = arr[i];
            }
            if (count == 3)
            {
                return arr[i];
            }
        }

        return -1;
    }

    int search(vector<int> &arr, int x)
    {
        for (int i = 0; i <= arr.size(); i++)
        {
            if (x == arr[i])
            {
                return i;
            }
        }

        return -1;
    }

    int missingNum(int *arr, int size)
    {
        int n = size + 1;                 // actual size should be n
        int totalSum = (n * (n + 1)) / 2; // sum of first n natural numbers
        int arraySum = 0;

        for (int i = 0; i < size; i++)
        {
            arraySum += arr[i];
        }

        return totalSum - arraySum;
    }

    void sort012(vector<int> &arr)
    {
        int n = arr.size();
        int low = 0, mid = 0, high = arr[n - 1];
        while (mid <= high)
        {
            if (arr[mid] == 0)
            {
                swap(arr[low], arr[mid]);
                low++;
                mid++;
            }
            else if (mid == 1)
            {
                mid++;
            }
            else
            {
                swap(arr[mid], arr[high]);
                high--;
            }
        }
    }

    bool checkEqual(vector<int> &a, vector<int> &b)
    {
        // code here
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        for (int i = 0; i <= a.size(); i++)
        {
            if (a[i] != b[i])
            {
                return false;
            }
        }

        return true;
    }

    void rotate(vector<int> &arr)
    {
        int n = arr.size();
        int lastElement = arr[n - 1];

        for (int i = n - 1; i > 0; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[0] = lastElement;
    }

    void rotate(vector<int> &arr, int k)
    {
        for (int i = 1; i <= k; i++)
        {
            int firstElement = arr[0];
            for (int i = 0; i < arr.size() - 1; i++)
            {
                arr[i] = arr[i + 1];
            }
            arr[arr.size() - 1] = firstElement;
        }
    }

    bool isSubset(vector<int> &a, vector<int> &b)
    {
        unordered_map<int, int> aCounts;

        // Count occurrences in array a
        for (int x : a)
        {
            aCounts[x]++;
        }

        // Check if elements of b are in a
        for (int x : b)
        {
            if (aCounts.find(x) == aCounts.end() || aCounts[x] == 0)
            {
                return false;
            }
            aCounts[x]--;
        }

        return true;
    }

    vector<int> frequencyCount(vector<int> &arr)
    {
        int n = arr.size();
        unordered_map<int, int> freqMap;
        vector<int> result(n, 0); // Initialize result array with size n and all zeros

        // Count frequency of elements in arr[]
        for (int num : arr)
        {
            freqMap[num]++;
        }

        // Populate result array with frequencies based on 1-based index
        for (int i = 1; i <= n; i++)
        {
            result[i - 1] = freqMap[i]; // Store frequency of number (i) at index (i-1)
        }

        return result;
    }

    void printTwoDArray()
    {
        int arr[2][3] = {{
                             1,
                             2,
                             3,
                         },
                         {4, 5, 6}};
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
    }

};

int main()
{
    Arrays ar;
    vector<int> arr = {2, 3, 2, 3, 5};
    vector<int> arr2 = {1, 4, 8, 10};
    vector<vector<int>> mat = {{1, 4}, {2, 5}};
    int a[7] = {3, 9, 10, 20, 17, 5, 1};
    // int res1 =
    //   firstOne();
    // cout << res1 << "\n";

    // vector<int> res =
    // bool res =
    //   int res =
    // quickSort(arr, 0, 4);
    //   cout << res;
    // for (auto n : arr)
    // {
    //     cout << n << " ";
    // }

    //   cout<<result;
    //  vector<vector<int>> res3 = rotateMatrix(1,d);
    // cout<<result
    //  vector<int> res  = nthRowOfPascalTriangle(5);
    //  for (auto n : res)
    //     {
    //         cout << n << " ";
    //     }

    // for (auto num : res)
    // {
    //     for (auto n : num)
    //     {
    //         cout << n << " ";
    //     }
    //     cout << endl;
    // }
    auto ans = ar.frequencyCount(arr);
    return 0;
}
