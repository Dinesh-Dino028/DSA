#include <bits/stdc++.h>
using namespace std;

class BinarySearch
{
public:
    bool searchInSorted(vector<int> &arr, int k)
    {
        int n = arr.size();
        int low = 0, high = n - 1;
        int mid;

        while (low <= high)
        {
            mid = (low + high) / 2;
            if (arr[mid] == k)
            {
                return true;
            }
            else if (k > arr[mid])
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return false;
    }

    int findFloor(vector<int> &arr, int x)
    {
        int n = arr.size();
        int low = 0;
        int high = n - 1;
        int mid;
        int floorIndex = -1;

        while (low <= high)
        {
            mid = (low + high) / 2;

            if (arr[mid] <= x)
            {
                floorIndex = mid; // Update floorIndex to the current mid
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }

        return floorIndex; // Return the floor value or -1 if not found
    }

    int firstOccurance(vector<int> &arr, int n, int x)
    {
        int low = 0, high = n - 1;
        int mid;
        int first = -1;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (arr[mid] == x)
            {
                first = mid;
                high = mid - 1;
            }
            else if (arr[mid] < x)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return first;
    }

    int lastOccurance(vector<int> &arr, int n, int x)
    {
        int low = 0, high = n - 1;
        int mid;
        int last = -1;
        vector<int> res;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (arr[mid] == x)
            {
                last = mid;
                low = mid + 1;
            }
            else if (arr[mid] < x)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return last;
    }

    vector<int> find(vector<int> &arr, int x)
    {
        int n = arr.size();
        int firstO = firstOccurance(arr, n, x);
        if (firstO == -1)
        {
            return {-1, -1};
        }
        return {firstO, lastOccurance(arr, n, x)};
    }

    int missingNumber(vector<int> &nums)
    {
        int n = nums.size();
        int totalSum = n * (n + 1) / 2;
        int arraySum = accumulate(nums.begin(), nums.end(), 0);
        return totalSum - arraySum;
    }

    int floorSqrt(int n)
    {
        int low = 1;
        int high = n;
        int mid = 0;
        int value = 0;
        while (low <= high)
        {
            mid = (low + high) / 2;
            value = (mid * mid);
            if (value <= n)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return high;
    }

    int get(long long index);

    long long firstOne()
    {
        long long low = 0, high = 1;

        // Step 1: Find high bound where first 1 lies
        while (get(high) == 0)
        {
            low = high;
            high *= 2; // Double the search range
        }

        // Step 2: Binary search between low and high
        long long ans = -1;
        while (low <= high)
        {
            long long mid = low + (high - low) / 2;
            if (get(mid) == 1)
            {
                ans = mid;      // possible answer
                high = mid - 1; // look on left side
            }
            else
            {
                low = mid + 1; // move right
            }
        }

        return ans;
    }

    bool searchRotateArray(vector<int> &nums, int target)
    {
        int n = nums.size();
        int low = 0;
        int high = n - 1;
        int mid;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (nums[mid] == target)
            {
                return true;
            }
            // Handle duplicates
            if (nums[low] == nums[mid] && nums[mid] == nums[high])
            {
                low++;
                high--;
                continue;
            }
            // left sorted
            if (nums[low] <= nums[mid])
            {
                if (nums[low] <= target && target <= nums[mid])
                {
                    high = mid - 1;
                }
                else
                {
                    low = mid + 1;
                }
            }
            // right sorted
            else
            {
                if (target >= nums[mid] && target <= nums[high])
                {
                    low = mid + 1;
                }
                else
                {
                    high = mid - 1;
                }
            }
        }
        return false;
    }

    int missingNumber2(vector<int> &nums)
    {
        int n = nums.size();
        long long hashArr[n + 1] = {0};
        for (int i = 0; i < n; i++)
        {
            hashArr[nums[i]]++;
        }
        for (int j = 0; j <= n; j++)
        {
            if (hashArr[j] == 0)
            {
                return j;
            }
        }
        return -1;
    }

    int minNumber(int arr[], int low, int high)
    {
        int ans = INT_MAX;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (arr[low] <= arr[mid])
            {
                ans = min(ans, arr[low]);
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
                ans = min(ans, arr[mid]);
            }
        }
        return ans;
    }

    int findKRotation(vector<int> &arr)
    {
        int n = arr.size();
        int low = 0;
        int high = n - 1;
        int ans = INT_MAX;
        int index = -1;
        while (low <= high)
        {
            int mid = (low + high) / 2;

            if (arr[low] <= arr[high])
            {
                if (arr[low] < ans)
                {
                    index = low;
                    ans = arr[low];
                }
            }
            if (arr[low] <= arr[mid])
            {
                if (arr[low] < ans)
                {
                    index = low;
                    ans = arr[low];
                }
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
                if (arr[mid] < ans)
                {
                    index = mid;
                    ans = arr[mid];
                }
            }
        }
        return index;
    }

    int maxNumber(vector<int> arr)
    {
        int n = arr.size();
        int ans = 0;
        int low = 0;
        int high = n - 1;
        while (low <= high)
        {
            if (arr[low] <= arr[high])
            {
                return high;
            }
            int mid = (low + high) / 2;
            if (arr[low] <= arr[mid])
            {
                ans = max(ans, arr[mid]);
                low = mid + 1;
            }
            else
            {
                ans = max(ans, arr[high]);
                high = mid - 1;
            }
        }
        return ans;
    }

    int peakElement(vector<int> &arr)
    {
        int n = arr.size();
        if (n == 1)
        {
            return 0;
        }
        if (arr[0] > arr[1])
        {
            return 0;
        }
        if (arr[n - 1] > arr[n - 2])
        {
            return n - 1;
        }
        int low = 1, high = n - 2;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (arr[mid - 1] < arr[mid] && arr[mid] > arr[mid + 1])
            {
                return mid;
            }
            else if (arr[mid - 1] < arr[mid])
            {
                low = mid + 1;
            }
            else if (arr[mid] > arr[mid + 1])
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return -1;
    }

    int solve(int A[], int n1, int B)
    {
        int a[7] = {3, 9, 10, 20, 17, 5, 1};
        int low = 0, high = n1 - 1;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (mid < high && a[low] <= B && B <= a[mid])
            {
                high = mid - 1;
                if (B == mid)
                {
                    return mid;
                }
            }
            else if (a[mid] <= B && B <= a[high])
            {
                low = mid + 1;
                if (B == mid)
                {
                    return mid;
                }
            }
        }
        return -1;
    }

    // Matrix
    int lowerBound(vector<int> mat, int n, int x)
    {
        int low = 0;
        int high = n - 1;
        int ans = n; // Initialize to n to handle cases where no element >= x
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (mat[mid] >= x)
            {
                ans = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return ans;
    }

    vector<int> findMaxRow(vector<vector<int>> mat, int N)
    {
        int index = 0;
        int maxCount = 0;
        for (int i = 0; i <= N - 1; i++)
        {
            int count_ones = N - lowerBound(mat[i], N, 1);
            if (count_ones > maxCount)
            {
                maxCount = count_ones;
                index = i;
            }
        }
        return {index, maxCount};
    }

    bool binarySearchFn(vector<int> mat, int n, int x)
    {
        int low = 0;
        int high = n - 1;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (mat[low] <= x && x <= mat[high])
            {

                if (mat[low] == x || mat[mid] == x || mat[high] == x)
                {
                    return true;
                }
                if (mat[mid] < x)
                {
                    high = mid - 1;
                }
                else
                {
                    low = mid + 1;
                }
            }
            else
            {
                return false;
            }
        }
        return false;
    }

    bool searchMatrix(vector<vector<int>> &mat, int x)
    {
        int n = mat.size();
        int m = mat[0].size();
        int low = 0, high = n - 1;
        bool ans = false;

        for (int i = 0; i <= n - 1; i++)
        {
            ans = binarySearchFn(mat[i], m, x);
            if (ans == true)
            {
                return ans;
            }
        }

        return ans;
    }

    bool searchMatrix2(vector<vector<int>> &mat, int x)
    {
        int n = mat.size();
        int m = mat[0].size();
        int low = 0, high = n * m - 1;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            int row = mid / m;
            int col = mid % m;
            if (mat[row][col] == x)
            {
                return true;
            }
            else if (mat[row][col] < x)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }

        return false;
    }

    bool searchMatrix3(vector<vector<int>> &matrix, int target)
    {
        int n = matrix.size();
        int m = matrix[0].size();
        int row = 0, col = m - 1;
        while (row < n && col >= 0)
        {
            if (matrix[row][col] == target)
            {
                return true;
            }
            else if (matrix[row][col] < target)
            {
                row++;
            }
            else
            {
                col--;
            }
        }
        return false;
    }

    vector<int> findPeakGrid(vector<vector<int>> &mat)
    {
        int n = mat.size();
        int m = mat[0].size();

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                bool isPeak = true;

                // Check up
                if (i > 0 && mat[i][j] <= mat[i - 1][j])
                    isPeak = false;

                // Check down
                if (i < n - 1 && mat[i][j] <= mat[i + 1][j])
                    isPeak = false;

                // Check left
                if (j > 0 && mat[i][j] <= mat[i][j - 1])
                    isPeak = false;

                // Check right
                if (j < m - 1 && mat[i][j] <= mat[i][j + 1])
                    isPeak = false;

                if (isPeak)
                    return {i, j};
            }
        }

        return {0, 0}; // Return first element if no peak found
    }

    bool isPossible(vector<int> &stalls, int k, int minDist)
    {
        int cowsPlaced = 1; // Place the first cow at the first stall
        int lastPlaced = stalls[0];

        for (int i = 1; i < stalls.size(); i++)
        {
            if (stalls[i] - lastPlaced >= minDist)
            {
                cowsPlaced++;
                lastPlaced = stalls[i]; // Place a cow here

                if (cowsPlaced == k)
                    return true; // All cows are placed successfully
            }
        }
        return false;
    }

    int aggressiveCows(vector<int> &stalls, int k)
    {
        sort(stalls.begin(), stalls.end()); // Sort the stalls

        int left = 1, right = stalls.back() - stalls.front(), result = 0;

        while (left <= right)
        {
            int mid = left + (right - left) / 2; // Try a middle minimum distance

            if (isPossible(stalls, k, mid))
            {
                result = mid;   // Store the valid answer
                left = mid + 1; // Try for a larger minimum distance
            }
            else
            {
                right = mid - 1; // Reduce the search space
            }
        }

        return result;
    }

    int countStudents(vector<int> &arr, int pages)
    {
        int students = 1;
        long long pagesStudent = 0;
        for (int i = 0; i < arr.size(); i++)
        {
            if (pagesStudent + arr[i] <= pages)
            {
                pagesStudent += arr[i];
            }
            else
            {
                students++;
                pagesStudent = arr[i];
            }
        }
        return students;
    }

    int findPages(vector<int> &arr, int k)
    {
        int n = arr.size();
        if (k > n)
        {
            return -1;
        }
        int low = *max_element(arr.begin(), arr.end());
        int high = accumulate(arr.begin(), arr.end(), 0);
        while (low <= high)
        {
            int mid = (low + high) / 2;
            int students = countStudents(arr, mid);
            if (students > k)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return low;
    }

    // Function to count the number of painters needed
    int countPainters(vector<int> &arr, int maxWork)
    {
        int painters = 1;
        long long currentWork = 0;

        for (int i = 0; i < arr.size(); i++)
        {
            if (currentWork + arr[i] <= maxWork)
            {
                currentWork += arr[i]; // Add board to current painter
            }
            else
            {
                painters++; // Assign to a new painter
                currentWork = arr[i];
            }
        }
        return painters;
    }

    // Function to find the minimum time needed to paint all boards
    bool canPaint(vector<int> &boards, int k, long long maxTime)
    {
        long long total = 0;
        int painters = 1;

        for (int length : boards)
        {
            total += length;
            if (total > maxTime)
            { // need new painter
                painters++;
                total = length;
            }
            if (painters > k)
                return false;
        }
        return true;
    }

    long long minTime(vector<int> &boards, int k)
    {
        long long low = *max_element(boards.begin(), boards.end());
        long long high = accumulate(boards.begin(), boards.end(), 0LL);
        long long ans = high;

        while (low <= high)
        {
            long long mid = low + (high - low) / 2;
            if (canPaint(boards, k, mid))
            {
                ans = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return ans;
    }

    bool isPossible(vector<int> &bloomDay, int day, int m, int k)
    {
        int count = 0, noOfB = 0;
        for (int i = 0; i < bloomDay.size(); i++)
        {
            if (bloomDay[i] <= day)
            {
                count++;
            }
            else
            {
                noOfB += (count / k);
                count = 0;
            }
        }
        noOfB += (count / k);
        return noOfB >= m;
    }

    int minDays(vector<int> &bloomDay, int m, int k)
    {
        long long val = m * 1LL * k * 1LL;
        if (val > bloomDay.size())
        {
            return -1;
        }
        int n = bloomDay.size();
        int mini = INT_MAX;
        int maxi = INT_MIN;
        for (int i = 0; i < bloomDay.size(); i++)
        {
            mini = min(mini, bloomDay[i]);
            maxi = max(maxi, bloomDay[i]);
        }
        int low = mini, high = maxi;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (isPossible(bloomDay, mid, m, k))
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return low;
    }

    bool canShip(int arr[], int n, int d, int capacity)
    {
        int dayCount = 1;
        int currentLoad = 0;
        for (int i = 0; i < n; i++)
        {
            if (currentLoad + arr[i] > capacity)
            {
                dayCount++;
                currentLoad = 0;
            }
            currentLoad += arr[i];
        }
        return dayCount <= d;
    }

    int leastWeightCapacity(int arr[], int n, int d)
    {
        int low = *max_element(arr, arr + n);   // heaviest package
        int high = accumulate(arr, arr + n, 0); // total weight
        int ans = high;

        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (canShip(arr, n, d, mid))
            {
                ans = mid; // possible, try smaller
                high = mid - 1;
            }
            else
            {
                low = mid + 1; // not possible, need bigger capacity
            }
        }
        return ans;
    }

    int calculateMax(vector<int> &piles)
    {
        int maxi = INT_MIN;
        for (int i = 0; i < piles.size(); i++)
        {
            maxi = max(maxi, piles[i]);
        }
        return maxi;
    }

    long long calculateHrs(vector<int> &piles, int speed)
    {
        long long time = 0;
        for (int i = 0; i < piles.size(); i++)
        {
            time += (piles[i] + speed - 1) / speed;
        }
        return time;
    }

    int minEatingSpeed(vector<int> &piles, int h)
    {
        int low = 1, high = calculateMax(piles);
        long long totalHrs = 0;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            totalHrs = calculateHrs(piles, mid);
            if (totalHrs <= h)
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return low;
    }

    int findKthNumber(int m, int n, int k)
    {
        int low = 1, high = m * n, ans = -1;

        while (low <= high)
        {
            int mid = low + (high - low) / 2;

            // Count numbers <= mid
            long long count = 0;
            for (int i = 1; i <= m; i++)
            {
                count += min(mid / i, n);
            }

            if (count >= k)
            {
                ans = mid;
                high = mid - 1; // Try smaller
            }
            else
            {
                low = mid + 1; // Need bigger
            }
        }
        return ans;
    }
};

int main()
{
    BinarySearch bs;
    vector<int> arr = {3, 6, 7, 11};
    int ar[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 1};

    vector<vector<int>> mat = {{0, 0, 1,
                                0, 1, 1,
                                0, 0, 0}};
    auto ans = bs.findKthNumber(3, 3, 5);
    cout << ans;
    // for (auto a : ans)
    // {
    //     cout << a << " ";
    // }
    return 0;
}