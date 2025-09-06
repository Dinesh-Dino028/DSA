#include <bits/stdc++.h>
using namespace std;

class DynamicProgramming
{
private:
public:
    int factorial(int n)
    {
        int res = 1;
        for (int i = n; i > 0; i--)
        {
            res *= i;
        }
        return res;
    }

    int fibonacciRecur(int n) // Recurssion more time and space
    {
        if (n <= 1)
        {
            return n;
        }
        return fibonacciRecur(n - 1) + fibonacciRecur(n - 2);
    }
    int fibonacciUsingDP(int n, vector<int> &dp) // Memorization Top-Down (DP) TC - O(N) SC - O(N)+O(N)array
    {
        if (n <= 1)
        {
            return n;
        }
        if (dp[n] != -1)
        {
            return dp[n];
        }
        return dp[n] = fibonacciUsingDP(n - 1, dp) + fibonacciUsingDP(n - 2, dp);
    }
    int fibonacciTabulation(int n, vector<int> &dp) // Tabulation Bottom-Up  TC - O(N) SC - O(N)
    {
        dp[0] = 0;
        dp[1] = 1;

        for (int i = 2; i < n; i++)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
    int fibonacciUsingDPSpaceReduction(int n) // Space Optimization TC- O(N) SC- O(1)
    {
        int prev2 = 0;
        int prev = 1;
        for (int i = 2; i <= n; i++)
        {
            int curr = prev + prev2;
            prev2 = prev;
            prev = curr;
        }
        return prev;
    }

    int countWaysMemo(int n, vector<int> &memo)
    {
        if (n == 0)
        {
            return 1;
        }
        if (n < 0)
        {
            return 0;
        }
        if (memo[n] != -1)
        {
            return memo[n];
        }
        memo[n] = countWaysMemo(n - 1, memo) + countWaysMemo(n - 2, memo) + countWaysMemo(n - 3, memo);
        return memo[n];
    }
    int countWays(int n)
    {
        vector<int> memo(n + 1, -1);
        return countWaysMemo(n, memo);
    }

    int countWaysOrderMemo(int n, vector<int> &memo)
    {
        // your code here
        if (n == 0)
        {
            return 1;
        }
        if (n < 0)
        {
            return 0;
        }
        if (memo[n] != -1)
        {
            return memo[n];
        }

        memo[n] = countWaysOrderMemo(n - 1, memo) + countWaysOrderMemo(n - 2, memo);
        return memo[n];
    }
    int countWaysOrderDP(int n)
    {
        if (n < 0)
            return 0;
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            dp[i] += dp[i - 1];
            if (i - 2 >= 0)
                dp[i] += dp[i - 2];
        }
        return dp[n];
    }
    int countWays2(int n)
    {
        vector<int> memo(n + 1, -1);
        return countWaysOrderMemo(n, memo);
    }

    int nthStair(int n)
    {
        // When order does not matter, the answer is (n/2) + 1
        // For each possible number of 2-steps (from 0 to n/2), there is one unique way
        return n / 2 + 1;
    }

    // ✅ Plain recursion
    int robRecurssive(int index, vector<int> &nums)
    {
        if (index == 0)
            return nums[index];
        if (index < 0)
            return 0;
        int even = nums[index] + robRecurssive(index - 2, nums);
        int odd = 0 + robRecurssive(index - 1, nums);
        return max(even, odd);
    }
    int rob(vector<int> &nums)
    {
        return robRecurssive(nums.size() - 1, nums);
    }
    // ✅ Top-down memoization (n to 0)
    int robMemo(int index, vector<int> &nums, vector<int> &memo)
    {
        if (index == 0)
            return nums[index];
        if (index < 0)
            return 0;
        if (memo[index] != -1)
            return memo[index];
        int even = nums[index] + robMemo(index - 2, nums, memo);
        int odd = robMemo(index - 1, nums, memo);
        return memo[index] = max(even, odd);
    }
    int rob3(vector<int> &nums)
    {
        vector<int> memo(nums.size(), -1);
        return robMemo(nums.size() - 1, nums, memo);
    }
    // ✅ Bottom-up DP Tabulation (0 to n)
    int robDp(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        if (n == 1)
            return nums[0];
        vector<int> dp(n);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < n; i++)
        {
            dp[i] = max(nums[i] + dp[i - 2], dp[i - 1]);
        }
        return dp[n - 1];
    }
    // ✅ Space optimized
    int robSo(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;

        int prev2 = 0;
        int prev = nums[0]; // start with first house
        for (int i = 1; i < n; i++)
        {
            int take = nums[i] + prev2; // rob this house
            int skip = prev;            // skip this house
            int curr = max(take, skip); // best option
            prev2 = prev;
            prev = curr;
        }
        return prev;
    }
    int robHouse2(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1)
        {
            return nums[0];
        }
        if (n == 3)
        {
            int ans = 0;
            int temp = nums[0];
            ans = max(temp, nums[1]);
            ans = max(ans, nums[2]);
            return ans;
        }
        vector<int> temp1, temp2;
        for (int i = 0; i < n; i++)
        {
            if (i != 0)
            {
                temp1.push_back(nums[i]);
            }
            if (i != n - 1)
            {
                temp2.push_back(nums[i]);
            }
        }
        return max(robSo(temp1), robSo(temp2));
    }

    // recur and memorization
    int maximumPointsRecur(int day, int last, vector<vector<int>> &arr, vector<vector<int>> &memo)
    {
        int maxi = 0;
        if (day == 0)
        {
            for (int task = 0; task < 3; task++)
            {
                if (task != last)
                {
                    int point = arr[day][task];
                    maxi = max(maxi, point);
                }
            }
            return maxi;
        }
        if (memo[day][last] != -1)
        {
            return memo[day][last];
        }
        for (int task = 0; task < 3; task++)
        {
            if (task != last)
            {
                int point = arr[day][task] + maximumPointsRecur(day - 1, task, arr, memo);
                maxi = max(maxi, point);
            }
        }
        return memo[day][last] = maxi;
    }
    int maximumPoints(vector<vector<int>> &arr)
    {
        // Code here
        int n = arr.size();
        vector<vector<int>> memo(n, vector<int>(4, -1));
        return maximumPointsRecur(n - 1, 3, arr, memo);
    }
    // tabulation
    int maximumPointsTabulation(vector<vector<int>> &arr)
    {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(4, 0));
        dp[0][0] = max(arr[0][1], arr[0][2]);
        dp[0][1] = max(arr[0][0], arr[0][2]);
        dp[0][2] = max(arr[0][0], arr[0][1]);
        dp[0][3] = max({arr[0][0], arr[0][1], arr[0][2]});

        for (int day = 1; day < n; day++)
        {
            for (int last = 0; last < 4; last++)
            {
                dp[day][last] = 0;
                for (int task = 0; task < 3; task++)
                {
                    if (task != last)
                    {
                        int point = arr[day][task] + dp[day - 1][task];
                        dp[day][last] = max(dp[day][last], point);
                    }
                }
            }
        }
        return dp[n - 1][3];
    }
    // Space Optimization
    int maximumPointsSo(vector<vector<int>> &arr)
    {
        int n = arr.size();
        vector<int> prev(4, 0);
        prev[0] = max(arr[0][1], arr[0][2]);
        prev[1] = max(arr[0][0], arr[0][2]);
        prev[2] = max(arr[0][0], arr[0][1]);
        prev[3] = max({arr[0][0], arr[0][1], arr[0][2]});

        for (int day = 1; day < n; day++)
        {
            vector<int> temp(4, 0);
            for (int last = 0; last < 4; last++)
            {
                temp[last] = 0;
                for (int task = 0; task < 3; task++)
                {
                    if (task != last)
                    {
                        temp[last] = max(temp[last], arr[day][task] + prev[task]);
                    }
                }
            }
            prev = temp;
        }
        return prev[3];
    }

    int countPathsRecur(vector<int> adj[], int src, int dest)
    {
        if (src == dest)
        {
            return 1;
        }
        int total = 0;
        for (auto neighbour : adj[src])
        {
            total += countPathsRecur(adj, neighbour, dest);
        }
        return total;
    }
    int countPaths(vector<vector<int>> &edges, int V, int src, int dest)
    {
        vector<int> adj[V];
        for (auto edge : edges)
        {
            adj[edge[0]].push_back(edge[1]);
        }
        return countPathsRecur(adj, src, dest);
    }
    int countPathsMemoRecur(vector<int> adj[], int src, int dest, vector<int> &memo)
    {
        if (src == dest)
        {
            return 1;
        }
        if (memo[src] != -1)
        {
            return memo[src];
        }
        int total = 0;
        for (auto neighbour : adj[src])
        {
            total += countPathsMemoRecur(adj, neighbour, dest, memo);
        }
        return memo[src] = total;
    }
    int countPathsMemo(vector<vector<int>> &edges, int V, int src, int dest)
    {
        vector<int> adj[V];
        for (auto edge : edges)
        {
            adj[edge[0]].push_back(edge[1]);
        }
        vector<int> memo(V, -1);
        return countPathsMemoRecur(adj, src, dest, memo);
    }
    // Tabulation (Bottom-Up DP)
    void topoSort(int node, vector<int> adj[], vector<bool> &visited, vector<int> &order)
    {
        visited[node] = true;
        for (int neighbor : adj[node])
        {
            if (!visited[neighbor])
            {
                topoSort(neighbor, adj, visited, order);
            }
        }
        order.push_back(node);
    }
    int countPathsTabulation(vector<vector<int>> &edges, int V, int src, int dest)
    {
        vector<int> adj[V];
        for (auto &edge : edges)
            adj[edge[0]].push_back(edge[1]);

        vector<int> dp(V, 0);
        dp[dest] = 1;

        // Topological sort
        vector<bool> visited(V, false);
        vector<int> order;
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
                topoSort(i, adj, visited, order);
        }

        // Process in topological order
        reverse(order.begin(), order.end());
        for (int node : order)
        {
            for (int neighbor : adj[node])
            {
                dp[node] += dp[neighbor];
            }
        }

        return dp[src];
    }

    // tabulation
    int uniquePathsWithObstaclesRecur(int i, int j, vector<vector<int>> &obstacleGrid, vector<vector<int>> &dp)
    {
        if (i >= 0 && j >= 0 && obstacleGrid[i][j] == 1)
        {
            return 0;
        }
        if (i == 0 && j == 0)
        {
            return obstacleGrid[0][0] == 1 ? 0 : 1;
        }
        if (i < 0 || j < 0)
        {
            return 0;
        }
        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }
        int up = uniquePathsWithObstaclesRecur(i - 1, j, obstacleGrid, dp);
        int left = uniquePathsWithObstaclesRecur(i, j - 1, obstacleGrid, dp);
        return dp[i][j] = up + left;
    }
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return uniquePathsWithObstaclesRecur(m - 1, n - 1, obstacleGrid, dp);
    }
    // Space Optimization with 1D DP array
    int uniquePathsWithObstaclesSo(vector<vector<int>> &obstacleGrid)
    {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        vector<int> dp(n, 0);

        for (int i = 0; i < m; ++i)
        {
            vector<int> temp(n, 0); // Temporary row
            for (int j = 0; j < n; ++j)
            {
                if (obstacleGrid[i][j] == 1)
                {
                    temp[j] = 0; // Obstacle cell
                }
                else if (i == 0 && j == 0)
                {
                    temp[j] = 1; // Starting point
                }
                else
                {
                    int up = i > 0 ? dp[j] : 0;
                    int left = j > 0 ? temp[j - 1] : 0;
                    temp[j] = up + left;
                }
            }
            dp = temp; // Move to next row
        }

        return dp[n - 1];
    }

    // Recursion
    int numberOfPathsRecur(int i, int j)
    {
        if (i == 0 && j == 0)
        {
            return 1;
        }
        if (i < 0 || j < 0)
        {
            return 0;
        }

        int up = numberOfPathsRecur(i - 1, j);
        int left = numberOfPathsRecur(i, j - 1);
        return up + left;
    }
    int numberOfPaths(int m, int n)
    {
        return numberOfPathsRecur(m - 1, n - 1);
    }
    // Memorization
    int numberOfPathsRecurMemo(vector<vector<int>> &memo, int i, int j)
    {
        if (i == 0 && j == 0)
        {
            return 1;
        }
        if (i < 0 || j < 0)
        {
            return 0;
        }
        if (memo[i][j] != -1)
        {
            return memo[i][j];
        }
        int up = numberOfPathsRecurMemo(memo, i - 1, j);
        int left = numberOfPathsRecurMemo(memo, i, j - 1);
        return memo[i][j] = up + left;
    }
    int numberOfPathsRecurMemo(int m, int n)
    {
        // code here
        vector<vector<int>> memo(m, vector<int>(n, -1));

        return numberOfPathsRecurMemo(memo, m - 1, n - 1);
    }
    // Tabulation
    int uniquePathsTab(int m, int n)
    {
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == 0 && j == 0)
                    dp[i][j] = 1;
                else
                {
                    int up = (i > 0) ? dp[i - 1][j] : 0;
                    int left = (j > 0) ? dp[i][j - 1] : 0;
                    dp[i][j] = up + left;
                }
            }
        }
        return dp[m - 1][n - 1];
    }
    // Space Optimization
    int numberOfPathsRecurSo(int m, int n)
    {
        // code here
        vector<int> dp(m, 0);
        for (int i = 0; i < m; i++)
        {
            vector<int> temp(n, 0);
            for (int j = 0; j < n; j++)
            {
                if (i == 0 && j == 0)
                {
                    temp[j] = 1;
                }
                else if (i < 0 || j < 0)
                {
                    temp[j] = 0;
                }
                else
                {
                    int up = i > 0 ? dp[j] : 0;
                    int left = j > 0 ? temp[j - 1] : 0;
                    temp[j] = up + left;
                }
            }
            dp = temp;
        }
        return dp[n - 1];
    }

    // Recursion
    int minPathSumRecur(int i, int j, vector<vector<int>> &grid)
    {
        if (i == 0 && j == 0)
        {
            return grid[i][j];
        }
        if (i < 0 || j < 0)
        {
            return INT_MAX;
        }

        int up = minPathSumRecur(i - 1, j, grid);
        int left = minPathSumRecur(i, j - 1, grid);

        return grid[i][j] + min(up, left);
    }
    int minPathSum(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        return minPathSumRecur(n - 1, m - 1, grid);
    }
    // Memorization
    int minPathSumRecurMemo(int i, int j, vector<vector<int>> &grid, vector<vector<int>> &memo)
    {
        if (i == 0 && j == 0)
        {
            return grid[i][j];
        }
        if (i < 0 || j < 0)
        {
            return INT_MAX;
        }
        if (memo[i][j] != -1)
        {
            return memo[i][j];
        }
        int up = minPathSumRecurMemo(i - 1, j, grid, memo);
        int left = minPathSumRecurMemo(i, j - 1, grid, memo);
        memo[i][j] = grid[i][j] + min(up, left);
        return memo[i][j];
    }
    int minPathSumMemo(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> memo(n, vector<int>(m, -1));
        return minPathSumRecurMemo(n - 1, m - 1, grid, memo);
    }
    // Tabulation
    int minPathSumDp(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {

                if (i == 0 && j == 0)
                {
                    dp[i][j] = grid[i][j];
                }
                else
                {
                    int up = (i > 0) ? dp[i - 1][j] : INT_MAX;
                    int left = (j > 0) ? dp[i][j - 1] : INT_MAX;
                    dp[i][j] = grid[i][j] + min(up, left);
                }
            }
        }
        return dp[n - 1][m - 1];
    }
    // Space Optimization
    int minPathSumDpSo(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        vector<int> prev(m, 0);
        for (int i = 0; i < n; i++)
        {
            vector<int> curr(m, 0);
            for (int j = 0; j < m; j++)
            {
                if (i == 0 && j == 0)
                {
                    curr[j] = grid[i][j];
                }
                else if (i < 0 || j < 0)
                {
                    curr[j] = INT_MAX;
                }
                else
                {
                    int up = (i > 0) ? prev[j] : INT_MAX;
                    int left = (j > 0) ? curr[j - 1] : INT_MAX;
                    curr[j] = grid[i][j] + min(up, left);
                }
            }
            prev = curr;
        }
        return prev[m - 1];
    }

    int maximumPathRecur(int i, int j, vector<vector<int>> &mat)
    {
        int n = mat.size();
        int m = mat[0].size();
        if (i == n - 1)
        {
            // Last row, just return the value at (i, j)
            return mat[i][j];
        }
        int down = INT_MIN, downLeft = INT_MIN, downRight = INT_MIN;
        // Move directly down
        if (i + 1 < n)
            down = maximumPathRecur(i + 1, j, mat);
        // Move diagonally left
        if (i + 1 < n && j - 1 >= 0)
            downLeft = maximumPathRecur(i + 1, j - 1, mat);
        // Move diagonally right
        if (i + 1 < n && j + 1 < m)
            downRight = maximumPathRecur(i + 1, j + 1, mat);

        return mat[i][j] + max({down, downLeft, downRight});
    }
    int maximumPath(vector<vector<int>> &mat)
    {
        int n = mat.size();
        int m = mat[0].size();
        int result = INT_MIN;
        // Try starting from every column in the first row
        for (int j = 0; j < m; ++j)
        {
            result = max(result, maximumPathRecur(0, j, mat));
        }
        return result;
    }

    int maximumPathRecurMemo(int i, int j, vector<vector<int>> &mat, vector<vector<int>> &memo)
    {
        int n = mat.size();
        int m = mat[0].size();
        if (i == n - 1)
        {
            // Last row, just return the value at (i, j)
            return mat[i][j];
        }
        if (memo[i][j] != -1)
        {
            return memo[i][j];
        }
        int down = INT_MIN, downLeft = INT_MIN, downRight = INT_MIN;
        // Move directly down
        if (i + 1 < n)
            down = maximumPathRecurMemo(i + 1, j, mat, memo);
        // Move diagonally left
        if (i + 1 < n && j - 1 >= 0)
            downLeft = maximumPathRecurMemo(i + 1, j - 1, mat, memo);
        // Move diagonally right
        if (i + 1 < n && j + 1 < m)
            downRight = maximumPathRecurMemo(i + 1, j + 1, mat, memo);

        return memo[i][j] = mat[i][j] + max({down, downLeft, downRight});
    }
    int maximumPathMemo(vector<vector<int>> &mat)
    {
        int n = mat.size();
        int m = mat[0].size();
        int result = INT_MIN;
        vector<vector<int>> memo(n, vector<int>(m, -1));
        // Try starting from every column in the first row
        for (int j = 0; j < m; ++j)
        {
            result = max(result, maximumPathRecurMemo(0, j, mat, memo));
        }
        return result;
    }
    // Tabulation
    int maximumPathMemoDp(vector<vector<int>> &mat)
    {
        int n = mat.size();
        int m = mat[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (i == 0)
                {
                    dp[i][j] = mat[i][j];
                }
                else
                {
                    int up = dp[i - 1][j];
                    int upleft = (j > 0) ? dp[i - 1][j - 1] : INT_MIN;
                    int upright = (j + 1 < m) ? dp[i - 1][j + 1] : INT_MIN;
                    dp[i][j] = mat[i][j] + max({up, upleft, upright});
                }
            }
        }
        int result = INT_MIN;
        for (int j = 0; j < m; ++j)
        {
            result = max(result, dp[n - 1][j]);
        }
        return result;
    }
    // Space Optimization
    int maximumPathMemoSo(vector<vector<int>> &mat)
    {
        int n = mat.size();
        int m = mat[0].size();
        vector<int> prev(m, 0);
        for (int i = 0; i < n; i++)
        {
            vector<int> curr(m, 0);
            for (int j = 0; j < m; j++)
            {
                if (i == 0)
                {
                    curr[j] = mat[i][j];
                }
                else
                {
                    int leftDia = (j > 0) ? prev[j - 1] : INT_MIN;
                    int up = prev[j];
                    int rightDia = (j + 1 < m) ? prev[j + 1] : INT_MIN;
                    int maxi = max({leftDia, up, rightDia});
                    curr[j] = maxi + mat[i][j];
                }
            }
            prev = curr;
        }
        int result = INT_MIN;
        for (int j = 0; j < m; ++j)
        {
            result = max(result, prev[j]);
        }
        return result;
    }

    // Recurssion
    int minimumTotalRecur(int i, int j, int n, vector<vector<int>> &triangle)
    {
        if (i == n - 1)
        {
            return triangle[i][j];
        }

        int d = triangle[i][j] + minimumTotalRecur(i + 1, j, n, triangle);
        int dg = triangle[i][j] + minimumTotalRecur(i + 1, j + 1, n, triangle);

        return min(d, dg);
    }
    int minimumTotal(vector<vector<int>> &triangle)
    {
        int n = triangle.size();
        int m = triangle[0].size();
        return minimumTotalRecur(0, 0, n, triangle);
    }
    // Memorization
    int minimumTotalRecurMemo(int i, int j, int n, vector<vector<int>> &triangle, vector<vector<int>> memo)
    {
        if (i == n - 1)
        {
            return triangle[i][j];
        }

        if (memo[i][j] != -1)
        {
            return memo[i][j];
        }

        int d = triangle[i][j] + minimumTotalRecurMemo(i + 1, j, n, triangle, memo);
        int dg = triangle[i][j] + minimumTotalRecurMemo(i + 1, j + 1, n, triangle, memo);

        return memo[i][j] = min(d, dg);
    }
    int minimumTotalMemo(vector<vector<int>> &triangle)
    {
        int n = triangle.size();
        int m = triangle[0].size();
        vector<vector<int>> memo(n, vector<int>(n, -1));
        return minimumTotalRecurMemo(0, 0, n, triangle, memo);
    }
    // Tabulation
    int minimumTotalDp(vector<vector<int>> &triangle)
    {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Initialize bottom row
        for (int j = 0; j < n; j++)
        {
            dp[n - 1][j] = triangle[n - 1][j];
        }

        // Bottom-up DP
        for (int i = n - 2; i >= 0; i--)
        {
            for (int j = 0; j <= i; j++)
            {
                int d = triangle[i][j] + dp[i + 1][j];
                int dg = triangle[i][j] + dp[i + 1][j + 1];
                dp[i][j] = min(d, dg);
            }
        }

        return dp[0][0];
    }
    // Space optimization
    int minimumTotalSo(vector<vector<int>> &triangle)
    {
        int n = triangle.size();
        vector<int> prev(n, 0);
        for (int j = 0; j < n; j++)
        {
            prev[j] = triangle[n - 1][j];
        }

        for (int i = n - 2; i >= 0; i--)
        {
            vector<int> curr(n, 0);
            for (int j = 0; j <= i; j++)
            {
                int d = triangle[i][j] + prev[j];
                int dg = triangle[i][j] + prev[j + 1];
                curr[j] = min(d, dg);
            }
            prev = curr;
        }
        return prev[0];
    }

    int numberOfPathRecur(int i, int j, int k, vector<vector<int>> &arr)
    {
        if (i < 0 || j < 0 || k < 0)
        {
            return 0;
        }
        if (i == 0 && j == 0)
        {
            if (k == arr[0][0])
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        int up = numberOfPathRecur(i - 1, j, k - arr[i][j], arr);
        int left = numberOfPathRecur(i, j - 1, k - arr[i][j], arr);
        return up + left;
    }
    long long numberOfPath(int n, int k, vector<vector<int>> &arr)
    {
        return numberOfPathRecur(n - 1, n - 1, k, arr);
    }
    // Memorization
    int numberOfPathRecurMemo(int i, int j, int k, vector<vector<int>> &arr, vector<vector<vector<int>>> &dp)
    {
        // Base cases
        if (i < 0 || j < 0 || k < 0)
        {
            return 0;
        }

        if (i == 0 && j == 0)
        {
            if (k == arr[0][0])
            {
                return 1;
            }
            return 0;
        }

        if (dp[i][j][k] != -1)
        {
            return dp[i][j][k];
        }

        // Move up
        int up = numberOfPathRecurMemo(i - 1, j, k - arr[i][j], arr, dp);

        // Move left
        int left = numberOfPathRecurMemo(i, j - 1, k - arr[i][j], arr, dp);

        return dp[i][j][k] = up + left;
    }
    long long numberOfPathMemo(int n, int k, vector<vector<int>> &arr)
    {
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(k + 1, -1)));
        return numberOfPathRecurMemo(n - 1, n - 1, k, arr, dp);
    }
    long long numberOfPathDp(int n, int k, vector<vector<int>> &arr)
    {
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(k + 1, 0)));

        // Initialize base case
        for (int sum = 0; sum <= k; sum++)
        {
            if (sum == arr[0][0])
            {
                dp[0][0][sum] = 1;
            }
        }

        // Fill dp table
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int sum = 0; sum <= k; sum++)
                {
                    if (i == 0 && j == 0)
                        continue;

                    int up = 0;
                    int left = 0;

                    if (i > 0 && sum >= arr[i][j])
                    {
                        up = dp[i - 1][j][sum - arr[i][j]];
                    }
                    if (j > 0 && sum >= arr[i][j])
                    {
                        left = dp[i][j - 1][sum - arr[i][j]];
                    }

                    dp[i][j][sum] = up + left;
                }
            }
        }

        return dp[n - 1][n - 1][k];
    }

    int minFallingPathSumRecur(int i, int j, int m, vector<vector<int>> &matrix)
    {
        if (j < 0 || j >= m)
        {
            return INT_MAX;
        }
        if (i == 0)
        {
            return matrix[i][j];
        }

        int s = matrix[i][j] + minFallingPathSumRecur(i - 1, j, m, matrix);
        int ld = matrix[i][j] + minFallingPathSumRecur(i - 1, j - 1, m, matrix);
        int rd = matrix[i][j] + minFallingPathSumRecur(i - 1, j + 1, m, matrix);

        return min({s, ld, rd});
    }
    int minFallingPathSum(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        int m = matrix[0].size();
        int minSum = INT_MAX;
        for (int j = 0; j < m; j++)
        {
            minSum = min(minSum, minFallingPathSumRecur(n - 1, j, m, matrix));
        }
        return minSum;
    }
    int minFallingPathSumRecurMemo(int i, int j, int n, int m, vector<vector<int>> &matrix, vector<vector<int>> &memo)
    {
        if (j < 0 || j >= m)
            return INT_MAX; // Out of bounds
        if (i == n - 1)
            return matrix[i][j]; // Base case: bottom row

        if (memo[i][j] != -1)
            return memo[i][j];

        int down = matrix[i][j] + minFallingPathSumRecurMemo(i + 1, j, n, m, matrix, memo);
        int leftDiag = matrix[i][j] + minFallingPathSumRecurMemo(i + 1, j - 1, n, m, matrix, memo);
        int rightDiag = matrix[i][j] + minFallingPathSumRecurMemo(i + 1, j + 1, n, m, matrix, memo);

        return memo[i][j] = min({down, leftDiag, rightDiag});
    }
    int minFallingPathSumMemo(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        int m = matrix[0].size();
        int minSum = INT_MAX;
        vector<vector<int>> memo(n, vector<int>(m, -1));

        for (int j = 0; j < m; j++)
        {
            minSum = min(minSum, minFallingPathSumRecurMemo(0, j, n, m, matrix, memo));
        }
        return minSum;
    }
    // Tabulation
    int minFallingPathSumDp(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));

        // Initialize first row with matrix values
        for (int j = 0; j < m; j++)
        {
            dp[0][j] = matrix[0][j];
        }

        // Fill dp table
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int up = dp[i - 1][j];
                int leftDiag = (j - 1 >= 0) ? dp[i - 1][j - 1] : INT_MAX;
                int rightDiag = (j + 1 < m) ? dp[i - 1][j + 1] : INT_MAX;

                dp[i][j] = matrix[i][j] + min({up, leftDiag, rightDiag});
            }
        }

        // Find minimum value in last row
        int minSum = INT_MAX;
        for (int j = 0; j < m; j++)
        {
            minSum = min(minSum, dp[n - 1][j]);
        }

        return minSum;
    }
    // Space Optimization
    int minFallingPathSumSo(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<int> prev(m, 0);

        // Initialize first row with matrix values
        for (int j = 0; j < m; j++)
        {
            prev[j] = matrix[0][j];
        }

        for (int i = 1; i < n; i++)
        {
            vector<int> curr(m, 0);
            for (int j = 0; j < m; j++)
            {
                int up = prev[j];
                int leftDiag = (j - 1 >= 0) ? prev[j - 1] : INT_MAX;
                int rightDiag = (j + 1 < m) ? prev[j + 1] : INT_MAX;

                curr[j] = matrix[i][j] + min({up, leftDiag, rightDiag});
            }
            prev = curr;
        }

        // Find minimum value in last row
        int minSum = INT_MAX;
        for (int j = 0; j < m; j++)
        {
            minSum = min(minSum, prev[j]);
        }

        return minSum;
    }

    int minFallingPathSum2Recur(int i, int j, int m, vector<vector<int>> &grid)
    {
        if (j < 0 || j >= m)
        {
            return INT_MAX;
        }
        if (i == 0)
        {
            return grid[i][j];
        }

        int ld = minFallingPathSum2Recur(i - 1, j - 1, m, grid);
        int rd = minFallingPathSum2Recur(i - 1, j + 1, m, grid);

        return grid[i][j] + min(ld, rd);
    }
    int minFallingPathSum2(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        int mini = INT_MAX;
        for (int j = 0; j < m; j++)
        {
            mini = min(mini, minFallingPathSum2Recur(n - 1, j, m, grid));
        }
        return mini;
    }
    // Memorization
    int minFallingPathSum2RecurMemo(int i, int j, int m, vector<vector<int>> &grid, vector<vector<int>> &memo)
    {
        if (j < 0 || j >= m)
        {
            return INT_MAX;
        }
        if (i == 0)
        {
            return grid[i][j];
        }
        if (memo[i][j] != -1)
        {
            return memo[i][j];
        }
        int ld = minFallingPathSum2RecurMemo(i - 1, j - 1, m, grid, memo);
        int rd = minFallingPathSum2RecurMemo(i - 1, j + 1, m, grid, memo);

        return memo[i][j] = grid[i][j] + min(ld, rd);
    }
    int minFallingPathSum2Memo(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        int mini = INT_MAX;
        vector<vector<int>> memo(n, vector<int>(m, -1));
        for (int j = 0; j < m; j++)
        {
            mini = min(mini, minFallingPathSum2RecurMemo(n - 1, j, m, grid, memo));
        }
        return mini;
    }
    // Tabulation
    int minFallingPathSum2MemoDp(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));

        for (int j = 0; j < m; j++)
        {
            dp[0][j] = grid[0][j];
        }

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int ld = (j - 1 >= 0) ? dp[i - 1][j - 1] : INT_MAX;
                int rd = (j + 1 < m) ? dp[i - 1][j + 1] : INT_MAX;
                dp[i][j] = grid[i][j] + min(ld, rd);
            }
        }

        int mini = INT_MAX;
        for (int j = 0; j < m; j++)
        {
            mini = min(mini, dp[n - 1][j]);
        }

        return mini;
    }
    // Space Optimization
    int minFallingPathSum2MemoSo(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        vector<int> prev = grid[0]; // First row is the starting point

        for (int i = 1; i < n; i++)
        {
            vector<int> curr(m, INT_MAX);
            for (int j = 0; j < m; j++)
            {
                // We must choose the min value from previous row excluding the same column
                for (int k = 0; k < m; k++)
                {
                    if (k != j)
                    {
                        curr[j] = min(curr[j], grid[i][j] + prev[k]);
                    }
                }
            }
            prev = curr;
        }

        // Minimum from the last row
        return *min_element(prev.begin(), prev.end());
    }

    bool isSubsetSumRecur(int i, vector<int> &arr, int sum)
    {
        if (sum == 0)
        {
            return true;
        }
        if (i == 0)
        {
            return arr[0] == sum;
        }

        bool notTake = isSubsetSumRecur(i - 1, arr, sum);
        bool take = false;
        if (arr[i] <= sum)
        {
            take = isSubsetSumRecur(i - 1, arr, sum - arr[i]);
        }
        return take || notTake;
    }
    bool isSubsetSum(vector<int> &arr, int sum)
    {
        int n = arr.size();
        return isSubsetSumRecur(n - 1, arr, sum);
    }
    // Memorization
    bool isSubsetSumRecurMemo(int ind, vector<int> &arr, int sum, vector<vector<int>> &memo)
    {
        if (sum == 0)
        {
            return true;
        }
        if (ind == 0)
        {
            return arr[0] == sum;
        }
        if (memo[ind][sum] != -1)
        {
            return memo[ind][sum];
        }
        bool notTake = isSubsetSumRecurMemo(ind - 1, arr, sum, memo);
        bool take = false;
        if (arr[ind] <= sum)
        { // Changed < to <=
            take = isSubsetSumRecurMemo(ind - 1, arr, sum - arr[ind], memo);
        }
        return memo[ind][sum] = take || notTake; // Fixed return statement
    }
    bool isSubsetSumMemo(vector<int> &arr, int sum)
    {
        int n = arr.size();
        vector<vector<int>> memo(n, vector<int>(sum + 1, -1)); // Changed n+1 to n
        return isSubsetSumRecurMemo(n - 1, arr, sum, memo);
    }
    // Tabulation
    bool isSubsetSumDp(vector<int> &arr, int sum)
    {
        int n = arr.size();
        vector<vector<bool>> dp(n, vector<bool>(sum + 1, false));

        // Base cases
        for (int i = 0; i < n; i++)
        {
            dp[i][0] = true;
        }
        if (arr[0] <= sum)
        {
            dp[0][arr[0]] = true;
        }

        // Fill dp table
        for (int ind = 1; ind < n; ind++)
        {
            for (int target = 1; target <= sum; target++)
            {
                bool notTake = dp[ind - 1][target];
                bool take = false;
                if (arr[ind] <= target)
                {
                    take = dp[ind - 1][target - arr[ind]];
                }
                dp[ind][target] = take || notTake;
            }
        }

        return dp[n - 1][sum];
    }
    // Space Optimization
    bool isSubsetSumSo(vector<int> &arr, int sum)
    {
        int n = arr.size();
        vector<bool> prev(sum + 1, false);

        // Base cases
        prev[0] = true;
        if (arr[0] <= sum)
        {
            prev[arr[0]] = true;
        }

        // Fill table
        for (int ind = 1; ind < n; ind++)
        {
            vector<bool> curr(sum + 1, false);
            curr[0] = true;
            for (int target = 1; target <= sum; target++)
            {
                bool notTake = prev[target];
                bool take = false;
                if (arr[ind] <= target)
                {
                    take = prev[target - arr[ind]];
                }
                curr[target] = take || notTake;
            }
            prev = curr;
        }

        return prev[sum];
    }

    int perfectSumRecur(int i, vector<int> &arr, int target)
    {
        if (target == 0)
        {
            return 1;
        }

        if (i == 0)
            return target == arr[i];

        int notTake = perfectSumRecur(i - 1, arr, target);
        int take = 0;

        if (target >= arr[i])
        {
            take = perfectSumRecur(i - 1, arr, target - arr[i]);
        }

        return take + notTake;
    }
    int perfectSum(vector<int> &arr, int target)
    {
        // code here
        int n = arr.size();
        return perfectSumRecur(n - 1, arr, target);
    }
    // Memorization
    int perfectSumRecurMemo(int i, vector<int> &arr, int target, vector<vector<int>> &memo)
    {
        const int MOD = 1e9 + 7;

        if (target == 0)
            return 1;

        if (i == 0)
            return (arr[i] == target);

        if (memo[i][target] != -1)
            return memo[i][target];

        int notTake = perfectSumRecurMemo(i - 1, arr, target, memo);
        int take = 0;

        if (target >= arr[i])
            take = perfectSumRecurMemo(i - 1, arr, target - arr[i], memo);

        return memo[i][target] = (take + notTake) % MOD;
    }
    int perfectSumMemo(vector<int> &arr, int target)
    {
        int n = arr.size();
        vector<vector<int>> memo(n, vector<int>(target + 1, -1));
        return perfectSumRecurMemo(n - 1, arr, target, memo);
    }
    // Tabulation
    int perfectSumDp(vector<int> &arr, int target)
    {
        const int MOD = 1e9 + 7;
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(target + 1, 0));

        // Initialize base cases
        dp[0][0] = 1;
        if (arr[0] <= target)
            dp[0][arr[0]] = 1;

        for (int i = 1; i < n; i++)
        {
            for (int sum = 0; sum <= target; sum++)
            {
                int notTake = dp[i - 1][sum];
                int take = 0;

                if (sum >= arr[i])
                    take = dp[i - 1][sum - arr[i]];

                dp[i][sum] = (take + notTake) % MOD;
            }
        }
        return dp[n - 1][target];
    }
    // Space Optimization
    int perfectSumSo(vector<int> &arr, int target)
    {
        const int MOD = 1e9 + 7;
        int n = arr.size();
        vector<int> prev(target + 1, 0), curr(target + 1, 0);

        // Base case:
        prev[0] = (arr[0] == 0) ? 2 : 1; // If 0, then 2 ways: pick or not pick
        if (arr[0] != 0 && arr[0] <= target)
            prev[arr[0]] = 1;

        for (int i = 1; i < n; i++)
        {
            curr[0] = (arr[i] == 0) ? (prev[0] * 2) % MOD : prev[0]; // handle 0s properly
            for (int sum = 1; sum <= target; sum++)
            {
                int notTake = prev[sum];
                int take = (sum >= arr[i]) ? prev[sum - arr[i]] : 0;

                curr[sum] = (take + notTake) % MOD;
            }
            prev = curr;
        }

        return prev[target];
    }

    bool equalPartition(vector<int> &arr)
    {
        int n = arr.size();
        int target = 0;
        for (int i = 0; i < n; i++)
        {
            target += arr[i];
        }
        int tar = target / 2;
        if (target % 2)
        {
            return false;
        }
        return isSubsetSumSo(arr, tar);
    }

    int minDifference(vector<int> &arr)
    {
        int n = arr.size();
        int totalSum = accumulate(arr.begin(), arr.end(), 0);

        int target = totalSum / 2;

        vector<bool> prev(target + 1, false), curr(target + 1, false);

        prev[0] = true;

        if (arr[0] <= target)
        {
            prev[arr[0]] = true;
        }

        for (int i = 1; i < n; i++)
        {
            curr[0] = true;
            for (int sum = 1; sum <= target; sum++)
            {
                bool notTake = prev[sum];
                bool take = (arr[i] <= sum) ? prev[sum - arr[i]] : false;
                curr[sum] = notTake || take;
            }
            prev = curr;
        }

        int minDiff = INT_MAX;
        for (int s1 = 0; s1 <= target; s1++)
        {
            if (prev[s1])
            {
                int s2 = totalSum - s1;
                minDiff = min(minDiff, abs(s2 - s1));
            }
        }
        return minDiff;
    }

    int knapsackRecur(int i, int W, vector<int> &val, vector<int> &wt)
    {
        if (i == 0)
        {
            if (wt[i] <= W)
            {
                return val[i];
            }
            else
            {
                return 0;
            }
        }

        int notTake = 0 + knapsackRecur(i - 1, W, val, wt);
        int take = INT_MIN;
        if (wt[i] <= W)
        {
            take = val[i] + knapsackRecur(i - 1, W - wt[i], val, wt);
        }
        return max(notTake, take);
    }
    int knapsack(int W, vector<int> &val, vector<int> &wt)
    {
        int n = val.size();
        return knapsackRecur(n - 1, W, val, wt);
    }
    // Memorization
    int knapsackRecurMemo(int i, int W, vector<int> &val, vector<int> &wt, vector<vector<int>> memo)
    {
        if (i == 0)
        {
            if (wt[i] <= W)
            {
                return val[i];
            }
            else
            {
                return 0;
            }
        }
        if (memo[i][W] != -1)
        {
            return memo[i][W];
        }
        int notTake = 0 + knapsackRecurMemo(i - 1, W, val, wt, memo);
        int take = INT_MIN;
        if (wt[i] <= W)
        {
            take = val[i] + knapsackRecurMemo(i - 1, W - wt[i], val, wt, memo);
        }
        return memo[i][W] = max(notTake, take);
    }
    int knapsackMemo(int W, vector<int> &val, vector<int> &wt)
    {
        int n = val.size();
        vector<vector<int>> memo(n, vector<int>(W + 1, -1));
        return knapsackRecurMemo(n - 1, W, val, wt, memo);
    }
    // Tabulation
    int knapsackDp(int W, vector<int> &val, vector<int> &wt)
    {
        int n = val.size();
        vector<vector<int>> dp(n, vector<int>(W + 1, 0));

        for (int w = wt[0]; w <= W; w++)
        {
            {
                dp[0][w] = val[0];
            }

            for (int i = 1; i < n; i++)
            {
                for (int we = 0; we <= W; we++)
                {
                    int notTake = 0 + dp[i - 1][W];
                    int take = INT_MIN;
                    if (wt[i] <= W)
                    {
                        take = val[i] + dp[i - 1][W];
                    }
                    dp[i][W] = max(notTake, take);
                }
            }
            return dp[n - 1][W];
        }
    }
    // Space Optimization
    int knapsackSo(int W, vector<int> &val, vector<int> &wt)
    {
        int n = val.size();
        vector<int> prev(W + 1, 0), curr(W + 1, 0);

        // Base case: Fill first row based on first item
        for (int w = wt[0]; w <= W; w++)
        {
            prev[w] = val[0];
        }

        for (int i = 1; i < n; i++)
        {
            for (int w = 0; w <= W; w++)
            {
                int notTake = prev[w];
                int take = INT_MIN;
                if (wt[i] <= w)
                {
                    take = val[i] + prev[w - wt[i]];
                }
                curr[w] = max(notTake, take);
            }
            prev = curr;
        }
        return prev[W];
    }

    int findMaxSumRecur(int i, vector<int> &arr)
    {
        if (i == 0)
        {
            return arr[i];
        }
        if (i < 0)
        {
            return 0;
        }
        int notTake = 0 + findMaxSumRecur(i - 1, arr);
        int take = (i - 2 >= 0) ? arr[i] + findMaxSumRecur(i - 2, arr) : INT_MIN;

        return max(notTake, take);
    }
    int findMaxSum(vector<int> &arr)
    {
        // code here
        int n = arr.size();
        return findMaxSumRecur(n - 1, arr);
    }
    // Memorization
    int findMaxSumRecurMemo(int i, vector<int> &arr, vector<int> memo)
    {
        if (i == 0)
        {
            return arr[i];
        }
        if (i < 0)
        {
            return 0;
        }
        if (memo[i] != -1)
        {
            return memo[i];
        }
        int notTake = 0 + findMaxSumRecurMemo(i - 1, arr, memo);
        int take = (i - 2 >= 0) ? arr[i] + findMaxSumRecurMemo(i - 2, arr, memo) : 0;

        return memo[i] = max(notTake, take);
    }
    int findMaxSumMemo(vector<int> &arr)
    {
        // code here
        int n = arr.size();
        vector<int> memo(n, -1);
        return findMaxSumRecurMemo(n - 1, arr, memo);
    }
    // Tabulation
    int findMaxSumDp(vector<int> &arr)
    {
        int n = arr.size();
        vector<int> dp(n, 0);
        dp[0] = arr[0];

        for (int i = 1; i < n; i++)
        {
            int notTake = dp[i - 1]; // Removed unnecessary 0 +
            int take = arr[i];
            if (i > 1)
            {
                take += dp[i - 2];
            }
            dp[i] = max(notTake, take);
        }
        return dp[n - 1];
    }
    // Space Optimization
    int findMaxSumSo(vector<int> &arr)
    {
        int n = arr.size();
        if (n == 0)
            return 0;

        int prev = arr[0];
        int prev2 = 0;

        for (int i = 1; i < n; i++)
        {
            int notTake = prev;
            int take = arr[i] + prev2;

            int curr = max(notTake, take);
            prev2 = prev;
            prev = curr;
        }
        return prev;
    }

    int countRecur(int ind, vector<int> &coins, int sum)
    {
        if (ind == 0)
        {
            return (sum % coins[ind] == 0);
        }

        int notTake = countRecur(ind - 1, coins, sum);
        int take = 0;
        if (sum >= coins[ind])
        {
            take = countRecur(ind, coins, sum - coins[ind]);
        }

        return take + notTake;
    }
    int count(vector<int> &coins, int sum)
    {
        int n = coins.size();
        return countRecur(n - 1, coins, sum);
    }
    // Memorization
    int countRecurMemo(int ind, vector<int> &coins, int sum, vector<vector<int>> &memo)
    {
        if (ind == 0)
        {
            return sum % coins[ind] == 0;
        }
        if (memo[ind][sum] != -1)
        {
            return memo[ind][sum];
        }
        int notTake = countRecurMemo(ind - 1, coins, sum, memo);
        int take = 0;
        if (sum >= coins[ind])
        {
            take = countRecurMemo(ind, coins, sum - coins[ind], memo);
        }

        return memo[ind][sum] = take + notTake;
    }
    int countMemo(vector<int> &coins, int sum)
    {
        int n = coins.size();
        vector<vector<int>> memo(n, vector<int>(sum + 1, -1));
        return countRecurMemo(n - 1, coins, sum, memo);
    }
    // Tabulation
    int countDp(vector<int> &coins, int sum)
    {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(sum + 1, 0));

        // Initialize base case for first coin
        for (int T = 0; T <= sum; T++)
        {
            dp[0][T] = (T % coins[0] == 0);
        }

        for (int i = 1; i < n; i++)
        {
            for (int s = 0; s <= sum; s++)
            {
                int notTake = dp[i - 1][s];
                int take = 0;
                if (s >= coins[i])
                {
                    take = dp[i][s - coins[i]];
                }

                dp[i][s] = take + notTake;
            }
        }
        return dp[n - 1][sum];
    }
    // Space Optimization
    int countSo(vector<int> &coins, int sum)
    {
        int n = coins.size();
        vector<int> prev(sum + 1, 0), curr(sum + 1, 0);

        // Initialize base case for first coin
        for (int T = 0; T <= sum; T++)
        {
            prev[T] = (T % coins[0] == 0);
        }

        for (int i = 1; i < n; i++)
        {
            for (int s = 0; s <= sum; s++)
            {
                int notTake = prev[s];
                int take = 0;
                if (s >= coins[i])
                {
                    take = curr[s - coins[i]];
                }

                curr[s] = take + notTake;
            }
            prev = curr;
        }
        return prev[sum];
    }

    int minCoinsRecur(int i, vector<int> &coins, int sum)
    {
        if (i == 0)
        {
            if (sum % coins[i] == 0)
            {
                return sum / coins[i];
            }
            else
            {
                return 1e9;
            }
        }

        int notTake = minCoinsRecur(i - 1, coins, sum);
        int take = INT_MAX;
        if (sum >= coins[i])
        {
            take = 1 + minCoinsRecur(i, coins, sum - coins[i]);
        }
        return min(take, notTake);
    }
    int minCoins(vector<int> &coins, int sum)
    {
        // code here
        int n = coins.size();
        return minCoinsRecur(n - 1, coins, sum);
    }
    // Memorization
    int minCoinsRecurMemo(int i, vector<int> &coins, int sum, vector<vector<int>> memo)
    {
        if (i == 0)
        {
            if (sum % coins[i] == 0)
            {
                return sum / coins[i];
            }
            else
            {
                return 1e9;
            }
        }
        if (memo[i][sum] != -1)
        {
            return memo[i][sum];
        }
        int notTake = minCoinsRecurMemo(i - 1, coins, sum, memo);
        int take = INT_MAX;
        if (sum >= coins[i])
        {
            take = 1 + minCoinsRecurMemo(i, coins, sum - coins[i], memo);
        }
        return memo[i][sum] = min(take, notTake);
    }
    int minCoinsMemo(vector<int> &coins, int sum)
    {
        // code here
        int n = coins.size();
        vector<vector<int>> memo(n, vector<int>(sum + 1, -1));
        return minCoinsRecurMemo(n - 1, coins, sum, memo);
    }
    // Tabulation
    int minCoinsDp(vector<int> &coins, int sum)
    {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(sum + 1, 0));

        // Initialize first row
        for (int s = 0; s <= sum; s++)
        {
            if (s % coins[0] == 0)
            {
                dp[0][s] = s / coins[0];
            }
            else
            {
                dp[0][s] = 1e9;
            }
        }

        // Fill rest of the table
        for (int i = 1; i < n; i++)
        {
            for (int s = 0; s <= sum; s++)
            {
                int notTake = dp[i - 1][s];
                int take = 1e9;
                if (s >= coins[i])
                {
                    take = 1 + dp[i][s - coins[i]];
                }
                dp[i][s] = min(take, notTake);
            }
        }
        return dp[n - 1][sum];
    }
    // Space Optimization
    int minCoinsSo(vector<int> &coins, int sum)
    {
        int n = coins.size();
        vector<int> prev(sum + 1, 0), curr(sum + 1, 0);
        // Initialize first row
        for (int s = 0; s <= sum; s++)
        {
            if (s % coins[0] == 0)
            {
                prev[s] = s / coins[0];
            }
            else
            {
                prev[s] = 1e9;
            }
        }

        // Fill rest of the table
        for (int i = 1; i < n; i++)
        {
            for (int s = 0; s <= sum; s++)
            {
                int notTake = prev[s];
                int take = 1e9;
                if (s >= coins[i])
                {
                    take = 1 + curr[s - coins[i]];
                }
                curr[s] = min(take, notTake);
            }
            prev = curr;
        }
        int ans = prev[sum];
        if (ans >= 1e9)
            return -1;
        return ans;
    }
    int cutRodRecur(int i, vector<int> &price, int n)
    {
        if (i == 0)
        {
            return n * price[i];
        }
        int notTake = 0 + cutRodRecur(i - 1, price, n);
        int take = INT_MIN;
        int rodLength = i + 1;
        if (rodLength <= n)
        {
            take = price[i] + cutRodRecur(i, price, n - rodLength);
        }
        return max(notTake, take);
    }
    int cutRod(vector<int> &price)
    {
        int n = price.size();
        return cutRodRecur(n - 1, price, n);
    }
    // Memorization
    int cutRodRecurMemo(int i, vector<int> &price, int n, vector<vector<int>> &memo)
    {
        if (i == 0)
        {
            return n * price[i];
        }
        if (memo[i][n] != -1)
        {
            return memo[i][n];
        }
        int notTake = 0 + cutRodRecurMemo(i - 1, price, n, memo);
        int take = INT_MIN;
        int rodLength = i + 1;
        if (rodLength <= n)
        {
            take = price[i] + cutRodRecurMemo(i, price, n - rodLength, memo);
        }
        return memo[i][n] = max(notTake, take);
    }
    int cutRodMemo(vector<int> &price)
    {
        int n = price.size();
        vector<vector<int>> memo(n + 1, vector<int>(n + 1, -1));
        return cutRodRecurMemo(n - 1, price, n, memo);
    }
    // Tabulation
    int cutRodDp(vector<int> &price)
    {
        int n = price.size();
        vector<vector<int>> dp(n, vector<int>(n + 1, 0));

        // Initialize first row
        for (int N = 0; N <= n; N++)
        {
            dp[0][N] = N * price[0];
        }

        for (int i = 1; i < n; i++)
        {
            for (int N = 0; N <= n; N++)
            {
                int notTake = dp[i - 1][N];
                int take = INT_MIN;
                int rodLength = i + 1;
                if (rodLength <= N)
                {
                    take = price[i] + dp[i][N - rodLength];
                }
                dp[i][N] = max(notTake, take);
            }
        }
        return dp[n - 1][n];
    }
    // Space Optimization
    int cutRodSo(vector<int> &price)
    {
        int n = price.size();
        vector<int> prev(n + 1, 0), curr(n + 1, 0);
        // Initialize first row
        for (int N = 0; N <= n; N++)
        {
            prev[N] = N * price[0];
        }

        for (int i = 1; i < n; i++)
        {
            for (int N = 0; N <= n; N++)
            {
                int notTake = prev[N];
                int take = INT_MIN;
                int rodLength = i + 1;
                if (rodLength <= N)
                {
                    take = price[i] + curr[N - rodLength];
                }
                curr[N] = max(notTake, take);
            }
            prev = curr;
        }
        return prev[n];
    }

    // Reused method from context
    int perfectSumDp2(vector<int> &nums, int sum)
    {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(sum + 1, 0));

        // Initialize base cases
        dp[0][0] = (nums[0] == 0) ? 2 : 1;
        if (nums[0] != 0 && nums[0] <= sum)
            dp[0][nums[0]] = 1;

        for (int i = 1; i < n; i++)
        {
            for (int s = 0; s <= sum; s++)
            {
                int notTake = dp[i - 1][s];
                int take = 0;
                if (nums[i] <= s)
                {
                    take = dp[i - 1][s - nums[i]];
                }
                dp[i][s] = take + notTake;
            }
        }
        return dp[n - 1][sum];
    }
    int findTargetSumWays(vector<int> &nums, int target)
    {
        int totalSum = 0;
        for (int num : nums)
            totalSum += num;

        // Not possible if abs(target) > totalSum
        if (abs(target) > totalSum)
            return 0;

        // s1 - s2 = target
        // s1 + s2 = totalSum
        // 2*s1 = target + totalSum
        // s1 = (target + totalSum)/2

        if ((target + totalSum) % 2 != 0)
            return 0;

        int sum = (target + totalSum) / 2;
        if (sum < 0)
            return 0;

        // Reuse perfectSumDp method since this is same as count subset sum with given sum
        return perfectSumDp2(nums, sum);
    }

    int minimumCostRecur(int i, int w, vector<int> &cost)
    {
        if (w == 0)
        {
            return 0;
        }
        if (i < 0)
        {
            return 1e9;
        }

        int notTake = minimumCostRecur(i - 1, w, cost);
        int take = INT_MAX;
        int packageWeight = i + 1;
        if (cost[i] != -1 && packageWeight <= w)
        {
            take = cost[i] + minimumCostRecur(i, w - packageWeight, cost);
        }
        return min(notTake, take);
    }
    int minimumCost(int n, int w, vector<int> &cost)
    {
        return minimumCostRecur(n - 1, w, cost);
    }
    // Memorization
    int minimumCostRecurMemo(int i, int w, vector<int> &cost, vector<vector<int>> &memo)
    {
        if (w == 0)
        {
            return 0;
        }
        if (i < 0)
        {
            return 1e9;
        }
        if (memo[i][w] != -1)
        {
            return memo[i][w];
        }
        int notTake = minimumCostRecurMemo(i - 1, w, cost, memo);
        int take = 1e9;
        int packageWeight = i + 1;
        if (cost[i] != -1 && packageWeight <= w)
        {
            take = cost[i] + minimumCostRecurMemo(i, w - packageWeight, cost, memo);
        }
        return memo[i][w] = min(notTake, take);
    }
    int minimumCostMemo(int n, int w, vector<int> &cost)
    {
        vector<vector<int>> memo(n, vector<int>(w + 1, -1));
        int ans = minimumCostRecurMemo(n - 1, w, cost, memo);
        return (ans >= 1e9) ? -1 : ans;
    }
    // Tabulation
    int minimumCostDp(int n, int w, vector<int> &cost)
    {
        vector<vector<int>> dp(n, vector<int>(w + 1, 1e9)); // dp[i][we] = min cost to get 'we' kg with 0..i packets

        // Initialize first row: only using 1st packet (1kg), index = 0
        for (int we = 0; we <= w; we++)
        {
            if (cost[0] != -1 && we % 1 == 0)
            {
                dp[0][we] = we * cost[0]; // only 1kg packets used
            }
        }

        for (int i = 1; i < n; i++)
        {
            int wt = i + 1; // because packet at cost[i] is for (i+1) kg
            for (int we = 0; we <= w; we++)
            {
                int notTake = dp[i - 1][we];
                int take = 1e9;
                if (cost[i] != -1 && wt <= we && dp[i][we - wt] != 1e9)
                {
                    take = cost[i] + dp[i][we - wt];
                }
                dp[i][we] = min(notTake, take);
            }
        }

        return (dp[n - 1][w] >= 1e9) ? -1 : dp[n - 1][w];
    }
    // Space Optimization
    int minimumCostSo(int n, int w, vector<int> &cost)
    {
        vector<int> prev(w + 1, 1e9);
        // Initialize first row: only using 1st packet (1kg), index = 0
        if (cost[0] != -1)
        {

            for (int we = 0; we <= w; we++)
            {
                prev[we] = we * cost[0]; // only 1kg packets used
            }
        }

        for (int i = 1; i < n; i++)
        {
            int wt = i + 1; // because packet at cost[i] is for (i+1) kg
            vector<int> curr(w + 1, 1e9);
            for (int we = 0; we <= w; we++)
            {
                int notTake = prev[we];
                int take = 1e9;
                if (cost[i] != -1 && wt <= we && curr[we - wt] != 1e9)
                {
                    take = cost[i] + prev[we - wt];
                }
                curr[we] = min(notTake, take);
            }
            prev = curr;
        }

        return (prev[w] >= 1e9) ? -1 : prev[w];
    }

    int knapSackRecur(int i, vector<int> &val, vector<int> &wt, int capacity)
    {
        if (capacity == 0)
        {
            return 0;
        }
        if (i == 0)
        {
            if (wt[i] <= capacity)
            {
                return (capacity / wt[i]) * val[i];
            }
        }

        int notTake = 0 + knapSackRecur(i - 1, val, wt, capacity);
        int take = INT_MIN;
        if (wt[i] <= capacity)
        {
            take = val[i] + knapSackRecur(i, val, wt, capacity - wt[i]);
        }
        return max(take, notTake);
    }
    int knapSack(vector<int> &val, vector<int> &wt, int capacity)
    {
        int n = val.size();
        return knapSackRecur(n - 1, val, wt, capacity);
    }
    // Memorization
    int knapSackRecurMemo(int i, vector<int> &val, vector<int> &wt, int capacity, vector<vector<int>> &memo)
    {
        if (capacity == 0)
        {
            return 0;
        }
        if (i == 0)
        {
            if (wt[i] <= capacity)
            {
                return (capacity / wt[i]) * val[i];
            }
            return 0;
        }
        if (memo[i][capacity] != -1)
        {
            return memo[i][capacity];
        }
        int notTake = 0 + knapSackRecurMemo(i - 1, val, wt, capacity, memo);
        int take = INT_MIN;
        if (val[i] <= capacity)
        {
            take = val[i] + knapSackRecurMemo(i, val, wt, capacity - wt[i], memo);
        }
        return memo[i][capacity] = max(take, notTake);
    }
    int knapSackMemo(vector<int> &val, vector<int> &wt, int capacity)
    {
        int n = val.size();
        vector<vector<int>> memo(n, vector<int>(capacity + 1, -1));
        return knapSackRecurMemo(n - 1, val, wt, capacity, memo);
    }
    // Tabulation
    int knapSackDp(vector<int> &val, vector<int> &wt, int capacity)
    {
        int n = val.size();
        vector<vector<int>> dp(n, vector<int>(capacity + 1, 0));

        for (int c = 0; c <= capacity; c++)
        {
            dp[0][c] = (c / wt[0]) * val[0];
        }

        for (int i = 1; i < n; i++)
        {
            for (int c = 0; c <= capacity; c++)
            {
                int notTake = 0 + dp[i - 1][c];
                int take = INT_MIN;
                if (val[i] <= c)
                {
                    take = val[i] + dp[i][c - wt[i]];
                }
                dp[i][c] = max(take, notTake);
            }
        }
        return dp[n - 1][capacity];
    }
    // Space Optimization
    int knapSackSo(vector<int> &val, vector<int> &wt, int capacity)
    {
        int n = val.size();
        vector<int> prev(capacity + 1);
        for (int c = 0; c <= capacity; c++)
        {
            prev[c] = (c / wt[0]) * val[0];
        }

        for (int i = 1; i < n; i++)
        {
            vector<int> curr(capacity + 1, 0);
            for (int c = 0; c <= capacity; c++)
            {
                int notTake = 0 + prev[c];
                int take = INT_MIN;
                if (wt[i] <= c)
                {
                    take = val[i] + curr[c - wt[i]];
                }
                curr[c] = max(take, notTake);
            }
            prev = curr;
        }
        return prev[capacity];
    }
    // Space Optimization 1D
    int knapSackSo1D(vector<int> &val, vector<int> &wt, int capacity)
    {
        int n = val.size();
        vector<int> prev(capacity + 1);
        for (int c = 0; c <= capacity; c++)
        {
            prev[c] = (c / wt[0]) * val[0];
        }

        for (int i = 1; i < n; i++)
        {
            for (int c = 0; c <= capacity; c++)
            {
                int notTake = 0 + prev[c];
                int take = INT_MIN;
                if (wt[i] <= c)
                {
                    take = val[i] + prev[c - wt[i]];
                }
                prev[c] = max(take, notTake);
            }
        }
        return prev[capacity];
    }

    // DP on longest increasing subsequence

    int lengthOfLISRecur(int ind, vector<int> &nums, int n, int prevInd)
    {
        if (ind == n)
        {
            return 0;
        }

        int len = 0 + lengthOfLISRecur(ind + 1, nums, n, prevInd);
        if (prevInd == -1 || nums[ind] > nums[prevInd])
        {
            len = max(len, 1 + lengthOfLISRecur(ind + 1, nums, n, ind));
        }
        return len;
    }
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        int prevInd = -1;
        return lengthOfLISRecur(0, nums, n, prevInd);
    }
    // Memorization
    int lengthOfLISRecurMemo(int ind, vector<int> &nums, int n, int prevInd, vector<vector<int>> &memo)
    {
        if (ind == n)
        {
            return 0;
        }
        if (memo[ind][prevInd + 1] != -1)
        {
            return memo[ind][prevInd + 1];
        }
        int len = 0 + lengthOfLISRecurMemo(ind + 1, nums, n, prevInd, memo);
        if (prevInd == -1 || nums[ind] > nums[prevInd])
        {
            len = max(len, 1 + lengthOfLISRecurMemo(ind + 1, nums, n, ind, memo));
        }
        return memo[ind][prevInd + 1] = len;
    }
    int lengthOfLISMemo(vector<int> &nums)
    {
        int n = nums.size();
        int prevInd = -1;
        vector<vector<int>> memo(n, vector<int>(n + 1, -1));
        return lengthOfLISRecurMemo(0, nums, n, prevInd, memo);
    }
    // Tabulation
    int lengthOfLISDp(vector<int> &nums)
    {
        int n = nums.size();
        int prevInd = -1;
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int ind = n - 1; ind >= 0; ind--)
        {
            for (int prevInd = ind - 1; prevInd >= -1; prevInd--)
            {
                int len = 0 + dp[ind + 1][prevInd + 1];
                if (prevInd == -1 || nums[ind] > nums[prevInd])
                {
                    len = max(len, 1 + dp[ind + 1][ind + 1]);
                }
                dp[ind][prevInd + 1] = len;
            }
        }
        return dp[0][-1 + 1];
    }
    // Space Optimization
    int lengthOfLISSo(vector<int> &nums)
    {
        int n = nums.size();
        int prevInd = -1;
        vector<int> next(n + 1, 0);
        vector<int> curr(n + 1, 0);

        for (int ind = n - 1; ind >= 0; ind--)
        {
            for (int prevInd = ind - 1; prevInd >= -1; prevInd--)
            {
                int len = 0 + next[prevInd + 1];
                if (prevInd == -1 || nums[ind] > nums[prevInd])
                {
                    len = max(len, 1 + next[ind + 1]);
                }
                curr[prevInd + 1] = len;
            }
            next = curr;
        }
        return next[-1 + 1];
    }
    // Space Optimization 1D
    int lengthOfLISSo1D(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> dp(n, 1);
        int maxi = 1;
        for (int i = 0; i < n; i++)
        {
            for (int prev = 0; prev < i; prev++)
            {
                if (nums[i] > nums[prev])
                {
                    dp[i] = max(dp[i], 1 + dp[prev]);
                }
            }
            maxi = max(maxi, dp[i]);
        }
        return maxi;
    }

    int LongestBitonicSequence(int n, vector<int> &nums)
    {
        vector<int> inc(n, 1); // Length of increasing sequence ending at i
        vector<int> dec(n, 1); // Length of decreasing sequence starting at i

        // Calculate increasing sequence lengths
        for (int i = 0; i < n; i++)
        {
            for (int prev = 0; prev < i; prev++)
            {
                if (nums[i] > nums[prev])
                {
                    inc[i] = max(inc[i], 1 + inc[prev]);
                }
            }
        }

        // Calculate decreasing sequence lengths
        for (int i = n - 1; i >= 0; i--)
        {
            for (int prev = n - 1; prev > i; prev--)
            {
                if (nums[i] > nums[prev])
                {
                    dec[i] = max(dec[i], 1 + dec[prev]);
                }
            }
        }

        // Find maximum bitonic sequence length
        int maxi = 0;
        for (int i = 0; i < n; i++)
        {
            if (inc[i] > 1 && dec[i] > 1)
            { // Only consider if both increasing and decreasing parts exist
                maxi = max(maxi, inc[i] + dec[i] - 1);
            }
        }

        return maxi == 0 ? 0 : maxi; // Return 0 if no bitonic sequence found
    }

    vector<int> largestDivisibleSubset(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return {};

        // Sort array to ensure divisibility property
        sort(nums.begin(), nums.end());

        vector<int> dp(n, 1);
        vector<int> hash(n);

        int lastIndex = 0;
        int maxi = 1;

        // Fill dp array and track indices
        for (int i = 0; i < n; i++)
        {
            hash[i] = i;
            for (int prev = 0; prev < i; prev++)
            {
                if (nums[i] % nums[prev] == 0 && 1 + dp[prev] > dp[i])
                {
                    dp[i] = 1 + dp[prev];
                    hash[i] = prev;
                }
            }
            if (dp[i] > maxi)
            {
                maxi = dp[i];
                lastIndex = i;
            }
        }

        // Reconstruct subsequence
        vector<int> ans;
        ans.push_back(nums[lastIndex]);
        while (hash[lastIndex] != lastIndex)
        {
            lastIndex = hash[lastIndex];
            ans.push_back(nums[lastIndex]);
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }

    int longestStrChain(vector<string> &words)
    {
        // Sort by length to process shorter strings first
        sort(words.begin(), words.end(), [](const string &a, const string &b)
             { return a.length() < b.length(); });

        // dp[i] stores length of longest chain ending at words[i]
        unordered_map<string, int> dp;
        int maxLen = 1;

        for (string word : words)
        {
            dp[word] = 1;
            // Try removing each character to find predecessor
            for (int i = 0; i < word.length(); i++)
            {
                string pred = word.substr(0, i) + word.substr(i + 1);
                if (dp.find(pred) != dp.end())
                {
                    dp[word] = max(dp[word], dp[pred] + 1);
                }
            }
            maxLen = max(maxLen, dp[word]);
        }

        return maxLen;
    }

    int findNumberOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;

        vector<int> dp(n, 1);    // Length of LIS ending at i
        vector<int> count(n, 1); // Number of LIS ending at i
        int maxLen = 1;

        for (int i = 0; i < n; i++)
        {
            for (int prev = 0; prev < i; prev++)
            {
                if (nums[i] > nums[prev])
                {
                    if (dp[prev] + 1 > dp[i])
                    {
                        dp[i] = dp[prev] + 1;
                        count[i] = count[prev];
                    }
                    else if (dp[prev] + 1 == dp[i])
                    {
                        count[i] += count[prev];
                    }
                }
            }
            maxLen = max(maxLen, dp[i]);
        }

        int result = 0;
        for (int i = 0; i < n; i++)
        {
            if (dp[i] == maxLen)
            {
                result += count[i];
            }
        }

        return result;
    }

    // DP on Strings
    int longestCommonSubsequenceRecr(int ind1, int ind2, string text1, string text2)
    {
        if (ind1 < 0 || ind2 < 0)
        {
            return 0;
        }

        if (text1[ind1] == text2[ind2])
        {
            return 1 + longestCommonSubsequenceRecr(ind1 - 1, ind2 - 1, text1, text2);
        }
        else
        {
            return max(longestCommonSubsequenceRecr(ind1 - 1, ind2, text1, text2), longestCommonSubsequenceRecr(ind1, ind2 - 1, text1, text2));
        }
    }
    int longestCommonSubsequence(string text1, string text2)
    {
        int ind1 = text1.size() - 1;
        int ind2 = text2.size() - 1;
        return longestCommonSubsequenceRecr(ind1, ind2, text1, text2);
    }
    // Memorization
    int longestCommonSubsequenceRecrMemo(int ind1, int ind2, string text1, string text2, vector<vector<int>> &memo)
    {
        if (ind1 < 0 || ind2 < 0)
        {
            return 0;
        }

        if (memo[ind1][ind2] != -1)
        {
            return memo[ind1][ind2];
        }

        if (text1[ind1] == text2[ind2])
        {
            return memo[ind1][ind2] = 1 + longestCommonSubsequenceRecrMemo(ind1 - 1, ind2 - 1, text1, text2, memo);
        }
        return memo[ind1][ind2] = max(longestCommonSubsequenceRecrMemo(ind1 - 1, ind2, text1, text2, memo), longestCommonSubsequenceRecrMemo(ind1, ind2 - 1, text1, text2, memo));
    }
    int longestCommonSubsequenceMemo(string text1, string text2)
    {
        int n = text1.size();
        int m = text2.size();
        vector<vector<int>> memo(n, vector<int>(m, -1));
        return longestCommonSubsequenceRecrMemo(n - 1, m - 1, text1, text2, memo);
    }
    // Tabulation (Botton - Up)
    int longestCommonSubsequenceDp(string text1, string text2)
    {
        int n = text1.size();
        int m = text2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int j = 0; j <= m; j++)
        {
            dp[0][j] = 0;
        }
        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = 0;
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (text1[i - 1] == text2[j - 1])
                {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[n][m];
    }

    // Print the LCS
    string constructLCS(string text1, string text2, vector<vector<int>> &dp)
    {
        int i = text1.size();
        int j = text2.size();
        string lcs = "";

        while (i > 0 && j > 0)
        {
            if (text1[i - 1] == text2[j - 1])
            {
                lcs += text1[i - 1];
                i--;
                j--;
            }
            else
            {
                if (dp[i - 1][j] > dp[i][j - 1])
                    i--;
                else
                    j--;
            }
        }

        reverse(lcs.begin(), lcs.end()); // since we built it backwards
        return lcs;
    }

    // Space Optimization
    int longestCommonSubsequenceSo(string text1, string text2)
    {
        int n = text1.size();
        int m = text2.size();
        vector<int> prev(m + 1, 0), curr(m + 1, 0); // Fix: Initialize prev and curr with size m+1 instead of n+1

        // Base case: first row is already initialized to 0

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (text1[i - 1] == text2[j - 1])
                {
                    curr[j] = 1 + prev[j - 1];
                }
                else
                {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            prev = curr;
        }
        return prev[m]; // Fix: Return prev[m] instead of curr[m] since we copied curr to prev
    }

    int longestPalindromeSubseq(string s)
    {
        string t = s;
        reverse(t.begin(), t.end());
        return longestCommonSubsequenceDp(s, t);
    }

    vector<string> allLCS(string &s1, string &s2)
    {

        int n = s1.size(), m = s2.size();

        // Step 1: Build the LCS DP table
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        // Step 2: Backtracking to find all distinct LCS strings
        set<string> lcsSet;

        function<void(int, int, string)> backtrack = [&](int i, int j, string curr)
        {
            if (i == 0 || j == 0)
            {
                reverse(curr.begin(), curr.end());
                lcsSet.insert(curr);
                return;
            }

            if (s1[i - 1] == s2[j - 1])
            {
                backtrack(i - 1, j - 1, curr + s1[i - 1]);
            }
            else
            {
                if (dp[i - 1][j] == dp[i][j])
                    backtrack(i - 1, j, curr);
                if (dp[i][j - 1] == dp[i][j])
                    backtrack(i, j - 1, curr);
            }
        };

        backtrack(n, m, "");

        // Convert set to vector and return
        return vector<string>(lcsSet.begin(), lcsSet.end());
    }

    int minInsertions(string s)
    {
        if (s.size() == 2)
        {
            return 1;
        }
        string t = s;
        reverse(t.begin(), t.end());
        int len = longestCommonSubsequenceDp(s, t);
        int diff = s.size() - len;
        return len > 1 ? diff : 0;
    }

    int minOperations(string &s1, string &s2)
    {
        int len = longestCommonSubsequenceDp(s1, s2);
        int n = s1.size();
        int m = s2.size();
        int ans = (n - len) + (m - len);
        return ans;
    }

    int shortestCommonSupersequence(string &s1, string &s2)
    {
        int len = longestCommonSubsequenceDp(s1, s2);
        int n = s1.size();
        int m = s2.size();
        int ans = (n - len) + (m - len) + len;
        return ans;
    }

    int longestCommonSubstr(string &s1, string &s2)
    {
        int n = s1.size();
        int m = s2.size();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

        for (int j = 0; j <= m; j++)
        {
            dp[0][j] = 0;
        }
        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = 0;
        }
        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (s1[i - 1] == s2[j - 1])
                {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    ans = max(ans, dp[i][j]);
                }
                else
                {
                    // dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    dp[i][j] = 0;
                }
            }
        }

        return ans;
    }

    string longestPalindrome(string &s)
    {
        int n = s.length();
        if (n < 2)
            return s;

        int start = 0;
        int maxLen = 1;

        vector<vector<bool>> dp(n, vector<bool>(n, false));

        // All substrings of length 1 are palindromes
        for (int i = 0; i < n; i++)
        {
            dp[i][i] = true;
        }

        // Check for substrings of length 2
        for (int i = 0; i < n - 1; i++)
        {
            if (s[i] == s[i + 1])
            {
                dp[i][i + 1] = true;
                start = i;
                maxLen = 2;
            }
        }

        // Check for lengths greater than 2
        for (int len = 3; len <= n; len++)
        {
            for (int i = 0; i < n - len + 1; i++)
            {
                int j = i + len - 1;

                if (s[i] == s[j] && dp[i + 1][j - 1])
                {
                    dp[i][j] = true;
                    if (len > maxLen)
                    {
                        start = i;
                        maxLen = len;
                    }
                }
            }
        }

        return s.substr(start, maxLen);
    }

    int LongestRepeatingSubsequence(string &s)
    {
        // Code here
        int n = s.size();
        int m = s.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

        for (int j = 0; j <= m; j++)
        {
            dp[0][j] = 0;
        }
        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = 0;
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (s[i - 1] == s[j - 1] && i != j)
                {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[n][m];
    }

    int editDistanceRecur(int i, int j, string &s1, string &s2)
    {
        if (i < 0)
        {
            return j + 1;
        }
        if (j < 0)
        {
            return i + 1;
        }

        if (s1[i] == s2[j])
        {
            return 0 + editDistanceRecur(i - 1, j - 1, s1, s2);
        }
        return 1 + min({editDistanceRecur(i, j - 1, s1, s2), editDistanceRecur(i - 1, j, s1, s2), editDistanceRecur(i - 1, j - 1, s1, s2)});
    }
    int editDistance(string &s1, string &s2)
    {
        int n = s1.size();
        int m = s2.size();
        return editDistanceRecur(n - 1, m - 1, s1, s2);
    }
    // Memorization
    int editDistanceRecurMemo(int i, int j, string &s1, string &s2, vector<vector<int>> &memo)
    {
        if (i < 0)
        {
            return j + 1;
        }
        if (j < 0)
        {
            return i + 1;
        }
        if (memo[i][j] != -1)
        {
            return memo[i][j];
        }
        if (s1[i] == s2[j])
        {
            return memo[i][j] = 0 + editDistanceRecurMemo(i - 1, j - 1, s1, s2, memo);
        }
        return memo[i][j] = 1 + min({editDistanceRecurMemo(i, j - 1, s1, s2, memo), editDistanceRecurMemo(i - 1, j, s1, s2, memo), editDistanceRecurMemo(i - 1, j - 1, s1, s2, memo)});
    }
    int editDistanceMemo(string &s1, string &s2)
    {
        int n = s1.size();
        int m = s2.size();
        vector<vector<int>> memo(n, vector<int>(m, -1));
        return editDistanceRecurMemo(n - 1, m - 1, s1, s2, memo);
    }
    // Tabulation
    int editDistanceDp(string &s1, string &s2)
    {
        int n = s1.size();
        int m = s2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));

        for (int j = 0; j < m; j++)
        {
            dp[0][j] = 0;
        }
        for (int i = 0; i < n; i++)
        {
            dp[i][0] = 0;
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {

                if (s1[i] == s2[j])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {
                    return dp[i][j] = 1 + min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]});
                }
            }
        }
        return dp[n][m];
    }
    // Space Optimization
    int editDistanceSo(string &s1, string &s2)
    {
        int n = s1.size();
        int m = s2.size();
        vector<int> prev(m + 1, 0), curr(m + 1, 0);

        // Initialize first row
        for (int j = 0; j <= m; j++)
        {
            prev[j] = j;
        }

        for (int i = 1; i <= n; i++)
        {
            curr[0] = i; // Initialize first column
            for (int j = 1; j <= m; j++)
            {
                if (s1[i - 1] == s2[j - 1])
                {
                    curr[j] = prev[j - 1];
                }
                else
                {
                    curr[j] = 1 + min({curr[j - 1],   // Insert
                                       prev[j],       // Delete
                                       prev[j - 1]}); // Replace
                }
            }
            prev = curr;
        }
        return prev[m];
    }

    int subseqCountRecur(int i, int j, string &txt, string &pat)
    {
        if (j < 0)
        {
            return 1;
        }
        if (i < 0)
        {
            return 0;
        }

        if (txt[i] == pat[j])
        {
            return (subseqCountRecur(i - 1, j - 1, txt, pat) + subseqCountRecur(i - 1, j, txt, pat));
        }
        return subseqCountRecur(i - 1, j, txt, pat);
    }
    int subseqCount(string &txt, string &pat)
    {
        int n = txt.size();
        int m = pat.size();

        return subseqCountRecur(n - 1, m - 1, txt, pat);
    }
    // Memorization
    int subseqCountRecurMemo(int i, int j, string &txt, string &pat, vector<vector<int>> &memo)
    {
        if (j < 0)
        {
            return 1;
        }
        if (i < 0)
        {
            return 0;
        }
        if (memo[i][j] != -1)
        {
            return memo[i][j];
        }
        if (txt[i] == pat[j])
        {
            return memo[i][j] = (subseqCountRecurMemo(i - 1, j - 1, txt, pat, memo) + subseqCountRecurMemo(i - 1, j, txt, pat, memo));
        }
        return memo[i][j] = subseqCountRecurMemo(i - 1, j, txt, pat, memo);
    }
    int subseqCountMemo(string &txt, string &pat)
    {
        int n = txt.size();
        int m = pat.size();
        vector<vector<int>> memo(n, vector<int>(m, -1));
        return subseqCountRecurMemo(n - 1, m - 1, txt, pat, memo);
    }
    // Tabulation
    int subseqCountDp(string &txt, string &pat)
    {
        int n = txt.size();
        int m = pat.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = 1;
        }

        for (int j = 1; j <= m; j++)
        {
            dp[0][j] = 0;
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (txt[i - 1] == pat[j - 1])
                {
                    dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]);
                }
                else
                {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n][m];
    }
    // Space Optimization
    int subseqCountSo(string &txt, string &pat)
    {
        int n = txt.size();
        int m = pat.size();
        vector<int> prev(m + 1, 0), curr(m + 1, 0);
        prev[0] = curr[0] = 1;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (txt[i - 1] == pat[j - 1])
                {
                    curr[j] = (prev[j - 1] + prev[j]);
                }
                else
                {
                    curr[j] = prev[j];
                }
            }
            prev = curr;
        }
        return prev[m];
    }
    // Space Optimization 1D Need to change j m to 1 to compute
    int subseqCountSo1D(string &txt, string &pat)
    {
        int n = txt.size();
        int m = pat.size();
        vector<int> prev(m + 1, 0);
        prev[0] = 1;

        for (int i = 1; i <= n; i++)
        {
            for (int j = m; j >= 1; j--)
            {
                if (txt[i - 1] == pat[j - 1])
                {
                    prev[j] = (prev[j - 1] + prev[j]);
                }
            }
        }
        return prev[m];
    }

    bool wildCardRecurMemo(int i, int j, string &txt, string &pat, vector<vector<int>> &memo)
    {
        // Base cases
        if (i < 0 && j < 0)
        {
            return true;
        }
        if (j < 0)
        {
            return false;
        }
        if (i < 0)
        {
            // If remaining pattern has only '*', return true
            for (int ii = 0; ii <= j; ii++)
            {
                if (pat[ii] != '*')
                {
                    return false;
                }
            }
            return true;
        }
        if (memo[i][j] != -1)
        {
            return memo[i][j];
        }

        // If characters match or pattern has '?'
        if (txt[i] == pat[j] || pat[j] == '?')
        {
            return memo[i][j] = wildCardRecurMemo(i - 1, j - 1, txt, pat, memo);
        }
        // If pattern has '*', try matching current char or skip '*'
        else if (pat[j] == '*')
        {
            return memo[i][j] = wildCardRecurMemo(i - 1, j, txt, pat, memo) || // Match current char
                                wildCardRecurMemo(i, j - 1, txt, pat, memo);   // Skip '*'
        }
        return memo[i][j] = false;
    }
    bool wildCardMemo(string &txt, string &pat)
    {
        int n = txt.size();
        int m = pat.size();
        vector<vector<int>> memo(n, vector<int>(m, -1));
        return wildCardRecurMemo(n - 1, m - 1, txt, pat, memo);
    }
    // Tabulation
    bool wildCardDp(string &txt, string &pat)
    {
        int n = txt.size();
        int m = pat.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

        dp[0][0] = true;
        for (int i = 1; i <= n; i++)
        {
            dp[i][0] = false;
        }

        for (int j = 1; j <= m; j++)
        {
            bool flag = true;
            for (int ii = 1; ii <= j; ii++)
            {
                if (pat[ii - 1] != '*')
                {
                    flag = false;
                    break;
                }
            }
            dp[0][j] = flag;
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                // If characters match or pattern has '?'
                if (txt[i - 1] == pat[j - 1] || pat[j - 1] == '?')
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                // If pattern has '*', try matching current char or skip '*'
                else if (pat[j - 1] == '*')
                {
                    dp[i][j] = (dp[i - 1][j] || // Match current char
                                dp[i][j - 1]);  // Skip '*'
                }
                else
                {
                    dp[i][j] = false;
                }
            }
        }
        return dp[n][m];
    }

    bool wordBreakRecur(int start, string &s, unordered_set<string> &dict, vector<int> &dp)
    {
        if (start == s.size())
        {
            return true;
        }
        if (dp[start] != -1)
        {
            return dp[start];
        }
        for (int end = start + 1; end <= s.size(); end++)
        {
            string prefix = s.substr(start, end - start);
            if (dict.find(prefix) != dict.end())
            {
                if (wordBreakRecur(end, s, dict, dp))
                {
                    return dp[start] = true;
                }
            }
        }
        return dp[start] = false;
    }
    bool wordBreak(string &s, vector<string> &dictionary)
    {
        unordered_set<string> dict(dictionary.begin(), dictionary.end());
        vector<int> dp(s.size(), -1);
        return wordBreakRecur(0, s, dict, dp);
    }

    vector<string> wordBreak2Recur(int start, unordered_set<string> &dict, string &s, string curr)
    {
        vector<string> result;

        if (start == s.size())
        {
            if (!curr.empty())
            {
                curr.pop_back(); // Remove trailing space
                result.push_back(curr);
            }
            return result;
        }

        for (int end = start + 1; end <= s.size(); end++)
        {
            string prefix = s.substr(start, end - start);
            if (dict.find(prefix) != dict.end())
            {
                vector<string> subResult = wordBreak2Recur(end, dict, s, curr + prefix + " ");
                result.insert(result.end(), subResult.begin(), subResult.end());
            }
        }
        return result;
    }
    vector<string> wordBreak2(vector<string> &dict, string &s)
    {
        unordered_set<string> dictt(dict.begin(), dict.end());
        return wordBreak2Recur(0, dictt, s, "");
    }

    // DP in stocks

    int maxProfit(vector<int> &prices)
    {
        int mini = prices[0];
        int profit = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            int cost = prices[i] - mini;
            profit = max(profit, cost);
            mini = min(mini, prices[i]);
        }
        return profit;
    }

    int maxProfit2(vector<int> &prices)
    {
        int mini = prices[0];
        int profit = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            int cost = prices[i] - mini;
            if (cost > 0)
            {
                profit += cost;
                mini = prices[i];
            }
            else
            {
                mini = min(mini, prices[i]);
            }
        }
        return profit;
    }

    int maxProfit2Recur(int ind, vector<int> &prices, int n, int buy)
    {
        if (ind == n)
        {
            return 0;
        }
        int profit = 0;
        if (buy)
        {
            profit = max(-prices[ind] + maxProfit2Recur(ind + 1, prices, n, 0),
                         0 + maxProfit2Recur(ind + 1, prices, n, 1));
        }
        else
        {
            profit = max(prices[ind] + maxProfit2Recur(ind + 1, prices, n, 1),
                         0 + maxProfit2Recur(ind + 1, prices, n, 0));
        }
        return profit;
    }
    int maxProfit2Re(vector<int> &prices)
    {
        int n = prices.size();
        return maxProfit2Recur(0, prices, n, 1);
    }
    // Memorization
    int maxProfit2RecurMemo(int ind, vector<int> &prices, int n, int buy, vector<vector<int>> &memo)
    {
        if (ind == n)
        {
            return 0;
        }
        if (memo[ind][buy] != -1)
        {
            return memo[ind][buy];
        }
        int profit = 0;
        if (buy)
        {
            profit = max(-prices[ind] + maxProfit2RecurMemo(ind + 1, prices, n, 0, memo),
                         0 + maxProfit2RecurMemo(ind + 1, prices, n, 1, memo));
        }
        else
        {
            profit = max(prices[ind] + maxProfit2RecurMemo(ind + 1, prices, n, 1, memo),
                         0 + maxProfit2RecurMemo(ind + 1, prices, n, 0, memo));
        }
        return memo[ind][buy] = profit;
    }
    int maxProfit2ReMemo(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> memo(n, vector<int>(n, -1));
        return maxProfit2RecurMemo(0, prices, n, 1, memo);
    }
    // Tabulation
    int maxProfit2ReDp(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        dp[n][0] = dp[n][1] = 0;

        for (int ind = n - 1; ind >= 0; ind--)
        {
            for (int buy = 0; buy <= 1; buy++)
            {
                int profit = 0;
                if (buy)
                {
                    dp[ind][buy] = max(-prices[ind] + dp[ind + 1][0],
                                       0 + dp[ind + 1][1]);
                }
                else
                {
                    dp[ind][buy] = max(prices[ind] + dp[ind + 1][1],
                                       0 + dp[ind + 1][0]);
                }
            }
        }
        return dp[0][1];
    }
    // Space Optimization
    int maxProfit2ReSo(vector<int> &prices)
    {
        int n = prices.size();
        vector<int> prev(2, 0), curr(2, 0);

        prev[0] = prev[1] = 0;

        for (int ind = n - 1; ind >= 0; ind--)
        {
            for (int buy = 0; buy <= 1; buy++)
            {
                int profit = 0;
                if (buy)
                {
                    profit = max(-prices[ind] + prev[0],
                                 0 + prev[1]);
                }
                else
                {
                    profit = max(prices[ind] + prev[1],
                                 0 + prev[0]);
                }
                curr[buy] = profit;
            }
            prev = curr;
        }
        return prev[1];
    }
    int maxProfit2ReSoVar(vector<int> &prices)
    {
        int n = prices.size();
        long long aheadNotBuy, aheadBuy, curBuy, curNotBuy;

        for (int ind = n - 1; ind >= 0; ind--)
        {

            curBuy = max(-prices[ind] + aheadNotBuy,
                         0 + aheadBuy);

            curNotBuy = max(prices[ind] + aheadBuy,
                            0 + aheadNotBuy);

            aheadBuy = curBuy;
            aheadNotBuy = curNotBuy;
        }
        return aheadBuy;
    }

    int maxProfit3Recur(int ind, int n, vector<int> &prices, int buy, int cap)
    {
        if (cap == 0)
        {
            return 0;
        }
        if (ind == n)
        {
            return 0;
        }
        int profit = 0;
        if (buy)
        {
            profit = max(-prices[ind] + maxProfit3Recur(ind + 1, n, prices, 0, cap),
                         0 + maxProfit3Recur(ind + 1, n, prices, 1, cap));
        }
        else
        {
            profit = max(prices[ind] + maxProfit3Recur(ind + 1, n, prices, 1, cap - 1),
                         0 + maxProfit3Recur(ind + 1, n, prices, 0, cap));
        }
        return profit;
    }
    int maxProfit3(vector<int> &prices)
    {
        int n = prices.size();
        int cap = 2;
        return maxProfit3Recur(0, n, prices, 1, cap);
    }
    // Memorization
    int maxProfit3RecurMemo(int ind, int n, vector<int> &prices, int buy, int cap, vector<vector<vector<int>>> &memo)
    {
        if (cap == 0 || ind == n)
        {
            return 0;
        }

        if (memo[ind][buy][cap] != -1)
        {
            return memo[ind][buy][cap];
        }
        int profit = 0;
        if (buy)
        {
            profit = max(-prices[ind] + maxProfit3RecurMemo(ind + 1, n, prices, 0, cap, memo),
                         0 + maxProfit3RecurMemo(ind + 1, n, prices, 1, cap, memo));
        }
        else
        {
            profit = max(prices[ind] + maxProfit3RecurMemo(ind + 1, n, prices, 1, cap - 1, memo),
                         0 + maxProfit3RecurMemo(ind + 1, n, prices, 0, cap, memo));
        }
        return memo[ind][buy][cap] = profit;
    }
    int maxProfit3Memo(vector<int> &prices)
    {
        int n = prices.size();
        int cap = 2;
        vector<vector<vector<int>>> memo(n, vector<vector<int>>(2, vector<int>(3, -1)));
        return maxProfit3RecurMemo(0, n, prices, 1, cap, memo);
    }
    // Tabulation
    int maxProfit3Dp(vector<int> &prices)
    {
        int n = prices.size();
        int cap = 2;
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));

        for (int ind = n - 1; ind >= 0; ind--)
        {
            for (int buy = 0; buy <= 1; buy++)
            {
                for (int cap = 1; cap <= 2; cap++)
                {
                    int profit = 0;
                    if (buy)
                    {
                        dp[ind][buy][cap] = max(-prices[ind] + dp[ind + 1][0][cap],
                                                0 + dp[ind + 1][1][cap]);
                    }
                    else
                    {
                        dp[ind][buy][cap] = max(prices[ind] + dp[ind + 1][1][cap - 1],
                                                0 + dp[ind + 1][0][cap]);
                    }
                }
            }
        }
        return dp[0][1][2];
    }
    // Space Optimization
    int maxProfit3So(vector<int> &prices)
    {
        int n = prices.size();
        int cap = 2;
        vector<vector<int>> after(2, vector<int>(3, 0));
        vector<vector<int>> curr(2, vector<int>(3, 0));

        for (int ind = n - 1; ind >= 0; ind--)
        {
            for (int buy = 0; buy <= 1; buy++)
            {
                for (int cap = 1; cap <= 2; cap++)
                {
                    int profit = 0;
                    if (buy)
                    {
                        curr[buy][cap] = max(-prices[ind] + after[0][cap],
                                             0 + after[1][cap]);
                    }
                    else
                    {
                        curr[buy][cap] = max(prices[ind] + after[1][cap - 1],
                                             0 + after[0][cap]);
                    }
                }
            }
            after = curr;
        }
        return curr[1][2];
    }

    int maxProfit4Recur(int ind, int n, int k, vector<int> &prices, int buy)
    {
        if (ind == n || k == 0)
        {
            return 0;
        }

        int profit = 0;

        if (buy)
        {
            return max(-prices[ind] + maxProfit4Recur(ind + 1, n, k, prices, 0),
                       0 + maxProfit4Recur(ind + 1, n, k, prices, 1));
        }
        else
        {
            return max(prices[ind] + maxProfit4Recur(ind + 1, n, k - 1, prices, 1),
                       0 + maxProfit4Recur(ind + 1, n, k, prices, 0));
        }
    }
    int maxProfit4(int k, vector<int> &prices)
    {
        int n = prices.size();
        return maxProfit4Recur(0, n, k, prices, 1);
    }
    int maxProfit4RecurTranNum(int ind, int n, int k, vector<int> &prices, int trans)
    {
        if (ind == n || trans == 2 * k)
        {
            return 0;
        }

        if (trans % 2 == 0)
        {
            return max(-prices[ind] + maxProfit4RecurTranNum(ind + 1, n, k, prices, trans + 1),
                       0 + maxProfit4RecurTranNum(ind + 1, n, k, prices, trans));
        }
        return max(prices[ind] + maxProfit4RecurTranNum(ind + 1, n, k, prices, trans + 1),
                   0 + maxProfit4RecurTranNum(ind + 1, n, k, prices, trans));
    }
    int maxProfit4TranNum(int k, vector<int> &prices)
    {
        int n = prices.size();
        return maxProfit4RecurTranNum(0, n, k, prices, 0);
    }
    // Memorization
    int maxProfit4RecurTranNumMemo(int ind, int n, int k, vector<int> &prices, int trans, vector<vector<int>> &memo)
    {
        if (ind == n || trans == 2 * k)
        {
            return 0;
        }
        if (memo[ind][trans] != -1)
        {
            return memo[ind][trans];
        }
        if (trans % 2 == 0)
        {
            return memo[ind][trans] = max(-prices[ind] + maxProfit4RecurTranNumMemo(ind + 1, n, k, prices, trans + 1, memo),
                                          0 + maxProfit4RecurTranNumMemo(ind + 1, n, k, prices, trans, memo));
        }
        return memo[ind][trans] = max(prices[ind] + maxProfit4RecurTranNumMemo(ind + 1, n, k, prices, trans + 1, memo),
                                      0 + maxProfit4RecurTranNumMemo(ind + 1, n, k, prices, trans, memo));
    }
    int maxProfit4TranNumMemo(int k, vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> memo(n, vector<int>(2 * k, -1));
        return maxProfit4RecurTranNumMemo(0, n, k, prices, 0, memo);
    }
    // Tabulation
    int maxProfit4TranNumDp(int k, vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2 * k + 1, 0));

        for (int ind = n - 1; ind >= 0; ind--)
        {
            for (int trans = 2 * k - 1; trans >= 0; trans--)
            {
                if (trans % 2 == 0)
                {
                    dp[ind][trans] = max(-prices[ind] + dp[ind + 1][trans + 1],
                                         0 + dp[ind + 1][trans]);
                }
                else
                {
                    dp[ind][trans] = max(prices[ind] + dp[ind + 1][trans + 1],
                                         0 + dp[ind + 1][trans]);
                }
            }
        }
        return dp[0][0];
    }
    // Space Optimization
    int maxProfit4TranNumSo(int k, vector<int> &prices)
    {
        int n = prices.size();
        vector<int> after(2 * k + 1, 0);
        vector<int> curr(2 * k + 1, 0);

        for (int ind = n - 1; ind >= 0; ind--)
        {
            for (int trans = 2 * k - 1; trans >= 0; trans--)
            {
                if (trans % 2 == 0)
                {
                    curr[trans] = max(-prices[ind] + after[trans + 1],
                                      0 + after[trans]);
                }
                else
                {
                    curr[trans] = max(prices[ind] + after[trans + 1],
                                      0 + after[trans]);
                }
            }
            after = curr;
        }
        return after[0];
    }

    int maxProfit5(vector<int> &prices)
    {
        int n = prices.size();

        int profit = 0;
        int mini = prices[0];
        for (int i = 1; i < n; i++)
        {
            int cost = prices[i] - mini;
            if (cost > profit)
            {
                profit += cost;
                i++;
                mini = 0;
            }
            if (i < n)
            {
                mini = min(mini, prices[i]);
            }
        }
        return profit;
    }
    int maxProfit5Recur(int ind, int n, vector<int> &prices, int buy)
    {
        if (ind >= n)
        {
            return 0;
        }
        int profit = 0;
        if (buy)
        {
            return profit = max(-prices[ind] + maxProfit5Recur(ind + 1, n, prices, 0),
                                0 + maxProfit5Recur(ind + 1, n, prices, 1));
        }
        else
        {
            return profit = max(prices[ind] + maxProfit5Recur(ind + 2, n, prices, 1),
                                0 + maxProfit5Recur(ind + 1, n, prices, 0));
        }
    }
    int maxProfit5Re(vector<int> &prices)
    {
        int n = prices.size();
        return maxProfit5Recur(0, n, prices, 1);
    }
    // Memorization
    int maxProfit5RecurMemo(int ind, int n, vector<int> &prices, int buy, vector<vector<int>> &memo)
    {
        if (ind >= n)
        {
            return 0;
        }
        if (memo[ind][buy] != -1)
        {
            return memo[ind][buy];
        }
        if (buy)
        {
            return memo[ind][buy] = max(-prices[ind] + maxProfit5RecurMemo(ind + 1, n, prices, 0, memo),
                                        0 + maxProfit5RecurMemo(ind + 1, n, prices, 1, memo));
        }
        else
        {
            return memo[ind][buy] = max(prices[ind] + maxProfit5RecurMemo(ind + 2, n, prices, 1, memo),
                                        0 + maxProfit5RecurMemo(ind + 1, n, prices, 0, memo));
        }
    }
    int maxProfit5ReMemo(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> memo(n, vector<int>(n, -1));
        return maxProfit5RecurMemo(0, n, prices, 1, memo);
    }
    // Tabulation
    int maxProfit5ReDp(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n + 2, vector<int>(2, 0));

        for (int ind = n - 1; ind >= 0; ind--)
        {
            for (int buy = 0; buy <= 1; buy++)
            {
                if (buy)
                {
                    dp[ind][buy] = max(-prices[ind] + dp[ind + 1][0],
                                       0 + dp[ind + 1][1]);
                }
                else
                {
                    dp[ind][buy] = max(prices[ind] + dp[ind + 2][1],
                                       0 + dp[ind + 1][0]);
                }
            }
        }
        return dp[0][1];
    }

    int maxProfit6Recur(int ind, int n, vector<int> &prices, int fee, int buy)
    {
        if (ind == n)
        {
            return 0;
        }

        int profit = 0;
        if (buy)
        {
            return profit = max(-prices[ind] + maxProfit6Recur(ind + 1, n, prices, fee, 0),
                                0 + maxProfit6Recur(ind + 1, n, prices, fee, 1));
        }
        else
        {
            return profit = max((prices[ind] + maxProfit6Recur(ind + 1, n, prices, fee, 1) - fee),
                                0 + maxProfit6Recur(ind + 1, n, prices, fee, 0));
        }
    }
    int maxProfit6(vector<int> &prices, int fee)
    {
        int n = prices.size();
        return maxProfit6Recur(0, n, prices, fee, 1);
    }
};

int main()
{
    DynamicProgramming dpObj;

    vector<int> arr = {1, 3, 7, 5, 10, 3};
    vector<int> arr2 = {1, 3, 4, 5};
    vector<vector<int>> vec = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    int n = 5;
    vector<int> dp(n + 1, -1);
    vector<vector<int>> grid = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    vector<string> words = {"i", "like", "gfg"};

    string str1 = "ilike";
    string str2 = "a?c*";
    auto ans =
        // dpObj.fibonacci(n);
        dpObj.maxProfit6(arr, 3);
    cout << ans << " ";
    // for (auto a : ans)
    // {
    //     cout << a << " ";
    // }
    return 0;
}