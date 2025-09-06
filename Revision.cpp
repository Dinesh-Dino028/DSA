#include <bits/stdc++.h>
using namespace std;

// LRU Cache
class LRUCache
{
private:
    int capacity;
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>>::iterator> mpp;

public:
    LRUCache(int cap)
    {
        capacity = cap;
    }

    int get(int key)
    {
        if (mpp.find(key) == mpp.end())
        {
            return -1;
        }
        auto it = mpp[key];
        int value = it->second;
        cache.erase(it);
        cache.push_front({key, value});
        mpp[key] = cache.begin();
        return value;
    }

    void put(int key, int val)
    {
        if (mpp.find(key) != mpp.end())
        {
            auto it = mpp[key];
            cache.erase(it);
        }
        else if (cache.size() == capacity)
        {
            auto last = cache.back();
            mpp.erase(last.first);
            cache.pop_back();
        }
        cache.push_front({key, val});
        mpp[key] = cache.begin();
    }
};

class disjointset
{
private:
    vector<int> size;
    vector<int> rank;
    vector<int> parent;

public:
    disjointset(int n)
    {
        size.resize(n + 1);
        rank.resize(n + 1, 0);
        parent.resize(n + 1);

        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUPar(int node)
    {
        if (node == parent[node])
        {
            return node;
        }
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v)
    {
        int ulP_u = findUPar(u);
        int ulP_v = findUPar(v);
        if (ulP_u == ulP_v)
        {
            return;
        }
        if (rank[ulP_u] < rank[ulP_v])
        {
            parent[ulP_u] = ulP_v;
        }
        else if (rank[ulP_v] < rank[ulP_u])
        {
            parent[ulP_v] = ulP_u;
        }
        else
        {
            parent[ulP_v] = ulP_u;
            ;
            rank[ulP_u]++;
        }
    }

    void unionBySize(int u, int v)
    {
        int ulP_u = findUPar(u);
        int ulP_v = findUPar(v);
        if (ulP_u == ulP_v)
        {
            return;
        }
        if (rank[ulP_u] < rank[ulP_v])
        {
            parent[ulP_u] = ulP_v;
            size[ulP_v] += size[ulP_u];
        }
        else
        {
            parent[ulP_v] = ulP_u;
            size[ulP_u] += size[ulP_v];
        }
    }
};

class Revision
{
public:
    int maximumSumSubarray(vector<int> &arr, int k)
    {
        int n = arr.size();
        if (k > n)
        {
            return 0;
        }
        int sum = 0;
        for (int i = 0; i < k; i++)
        {
            sum += arr[i];
        }
        int maxSum = sum;
        for (int i = k; i < n; i++)
        {
            sum += arr[i] - arr[i - k]; // remove first
            maxSum = max(maxSum, sum);
        }
        return maxSum;
    }

    vector<int> maxOfSubarrays(vector<int> &arr, int k)
    {
        int n = arr.size();
        vector<int> res;
        int maxi = INT_MIN;
        for (int i = 0; i < k; i++)
        {
            maxi = max(maxi, arr[i]);
        }
        res.push_back(maxi);
        for (int i = k; i < n; i++)
        {
            maxi = max(maxi, arr[i]);
            res.push_back(maxi);
        }
        return res;
    }

    vector<int> subarraySum(vector<int> &arr, int target)
    {
        int n = arr.size();
        int sum = 0;
        vector<int> ans;
        int left = 0, right = 0;
        while (right < n)
        {
            sum += arr[right];
            if (sum > target)
            {
                while (sum > target)
                {
                    sum -= arr[left];
                    left++;
                }
            }
            if (sum == target)
            {
                ans.push_back(left + 1);
                ans.push_back(right + 1);
                break;
            }
            right++;
        }
        if (ans.empty())
        {
            ans.push_back(-1);
        }
        return ans;
    }

    int smallestSubstring(string S)
    {
        int ans = INT_MAX;
        int left = 0, right = 0;
        int n = 3;
        unordered_map<char, int> mpp;
        while (right < S.size())
        {
            if (S[right] == '0' || S[right] == '1' || S[right] == '2')
            {
                mpp[S[right]]++;
            }
            if (mpp.size() == n)
            {
                while (mpp[S[left]] > 1)
                {
                    mpp[S[left]]--;
                    left++;
                }
                ans = min(ans, (right - left) + 1);
            }
            right++;
        }
        if (ans == INT_MAX)
            return -1;
        return ans;
    }

    void recurAllSubsets(int index, vector<int> &arr, vector<int> &current, int &n, vector<vector<int>> &ans)
    {
        if (find(ans.begin(), ans.end(), current) == ans.end())
        {
            ans.push_back(current);
        }
        for (int i = index; i < n; i++)
        {
            if (i > 0 && arr[i] == arr[i - 1])
            {
                continue;
            }
            current.push_back(arr[i]);
            recurAllSubsets(i + 1, arr, current, n, ans);
            current.pop_back();
        }
    }
    // Function to find all possible unique subsets.
    vector<vector<int>> AllSubsets(vector<int> arr, int n)
    {
        vector<vector<int>> ans;
        vector<int> current;
        sort(arr.begin(), arr.end());
        recurAllSubsets(0, arr, current, n, ans);
        return ans;
    }

    void findPermutationRecur(string &s, vector<char> &ds, vector<string> &ans, vector<int> &freq)
    {
        if (ds.size() == s.size())
        {
            ans.push_back(string(ds.begin(), ds.end()));
            return;
        }
        for (int i = 0; i < s.size(); i++)
        {
            if (i > 0 && s[i] == s[i - 1] && !freq[i - 1])
            {
                continue; // skip duplicate
            }
            if (!freq[i])
            {
                freq[i] = 1;
                ds.push_back(s.at(i));
                findPermutationRecur(s, ds, ans, freq);
                freq[i] = 0;
                ds.pop_back();
            }
        }
    }
    vector<string> findPermutation(string &s)
    {
        vector<string> ans;
        vector<char> ds;
        int n = s.size();
        sort(s.begin(), s.end());
        vector<int> freq(n, 0);
        findPermutationRecur(s, ds, ans, freq);
        return ans;
    }

    void combinationSumRecur(int index, vector<int> &arr, int target, vector<int> &ds, vector<vector<int>> &ans)
    {
        if (index == arr.size())
        {
            if (target == 0)
            {
                ans.push_back(ds);
            }
            return;
        }
        if (arr[index] <= target)
        {
            ds.push_back(arr[index]);
            combinationSumRecur(index, arr, target - arr[index], ds, ans);
            ds.pop_back();
        }
        combinationSumRecur(index + 1, arr, target, ds, ans);
    }
    vector<vector<int>> combinationSum(vector<int> &arr, int target)
    {
        // Your code here
        vector<vector<int>> ans;
        vector<int> ds;
        combinationSumRecur(0, arr, target, ds, ans);
        return ans;
    }

    void subsetsRecur(int index, vector<int> &arr, vector<vector<int>> &ans, vector<int> &cur)
    {
        ans.push_back(cur);
        for (int i = index; i < arr.size(); i++)
        {
            cur.push_back(arr[i]);
            subsetsRecur(i + 1, arr, ans, cur);
            cur.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int> &arr)
    {
        vector<vector<int>> ans;
        vector<int> cur;
        sort(arr.begin(), arr.end());
        subsetsRecur(0, arr, ans, cur);
        return ans;
    }

    void recurGenerateParentheses(int open, int close, string &s, vector<string> &res, int n)
    {
        if (open == n && close == n)
        {
            res.push_back(s);
            return;
        }

        if (open < n)
        {
            s.append("(");
            recurGenerateParentheses(open + 1, close, s, res, n);
            s.pop_back();
        }

        if (close < open)
        {
            s.append(")");
            recurGenerateParentheses(open, close + 1, s, res, n);
            s.pop_back();
        }
    }
    vector<string> generateParentheses(int n)
    {
        // only add open parentheses if open < n
        // only add close parentheses if close < open
        // valid if open == n and close == n
        vector<string> res;
        string s;
        if (n % 2 != 0)
        {
            return res;
        }
        int length = n / 2;
        recurGenerateParentheses(0, 0, s, res, length);
        return res;
    }

    bool check(string s)
    {
        int n = s.size();
        if (n <= 0 || n > 3)
        {
            return false;
        }
        if (s[0] == '0' && n > 1)
        {
            return false;
        }
        int temp = stoi(s);
        if (temp < 0 || temp > 255)
        {
            return false;
        }
        return true;
    }
    string generateIPAddress(int n, string &s, int i, int j, int k)
    {
        string s1 = s.substr(0, i + 1);
        string s2 = s.substr(i + 1, j - i);
        string s3 = s.substr(j + 1, k - j);
        string s4 = s.substr(k + 1, n - 1 - k);

        if (check(s1) && check(s2) && check(s3) && check(s4))
        {
            return s1 + "." + s2 + "." + s3 + "." + s4;
        }
        return "";
    }
    vector<string> generateIp(string s)
    {
        int n = s.size();
        vector<string> ans;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                for (int k = j + 1; k < n; k++)
                {
                    string str = generateIPAddress(n, s, i, j, k);
                    if (str.length() > 0)
                    {
                        ans.push_back(str);
                    }
                }
            }
        }
        return ans;
    }

    string decodedString(string &s)
    {
        stack<int> counts;
        stack<string> resultString;
        string result;
        int i = 0;
        while (i < s.size())
        {
            if (isdigit(s[i]))
            {
                int count = 0;
                while (i < s.size() && isdigit(s[i]))
                {
                    count = count * 10 + s[i] - '0';
                    i++;
                }
                counts.push(count);
            }
            else if (s[i] == '[')
            {
                resultString.push(result);
                result = "";
                i++;
            }
            else if (s[i] == ']')
            {
                string temp = resultString.top();
                resultString.pop();
                int times = counts.top();
                counts.pop();
                for (int j = 0; j < times; j++)
                {
                    temp += result;
                }
                result = temp;
                i++;
            }
            else
            {
                result += s[i];
                i++;
            }
        }
        return result;
    }

    bool isValid(int row, int col, int k, vector<vector<int>> &board)
    {
        for (int i = 0; i < 9; i++)
        {
            if (board[row][i] == k)
            {
                return false;
            }
            if (board[i][col] == k)
            {
                return false;
            }
            if (board[(3 * (row / 3)) + i / 3][3 * (col / 3) + i % 3] == k)
            {
                return false;
            }
        }
        return true;
    }
    bool solveSudokuRecur(vector<vector<int>> &board)
    {
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                if (board[i][j] == 0)
                {
                    for (int k = 1; k <= 9; k++)
                    {
                        if (isValid(i, j, k, board))
                        {
                            board[i][j] = k;
                            if (solveSudokuRecur(board))
                            {
                                return true;
                            }
                            else
                            {
                                board[i][j] = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    void solveSudoku(vector<vector<int>> &mat)
    {
        solveSudokuRecur(mat);
    }

    vector<int> bfs(vector<vector<int>> &adj)
    {
        vector<int> vis(adj.size(), 0);
        vector<int> bfs;
        queue<int> q;
        q.push(0); // starting
        vis[0] = 1;
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            bfs.push_back(node);
            for (auto it : adj[node])
            { // going through the adjecent
                if (!vis[it])
                {
                    vis[it] = 1;
                    q.push(it);
                }
            }
        }
        return bfs;
    }

    void dfs(int node, vector<vector<int>> &adj, vector<int> &vis, vector<int> &ls)
    {
        vis[node] = 1;
        ls.push_back(node);

        for (auto it : adj[node])
        {
            if (!vis[it])
            {
                dfs(it, adj, vis, ls);
            }
        }
    }
    vector<int> dfs(vector<vector<int>> &adj)
    {
        vector<int> vis(adj.size(), 0);
        vector<int> ls;
        int node = 0;
        dfs(0, adj, vis, ls);
        return ls;
    }

    bool dfsCheck(int node, vector<vector<int>> &adj, vector<int> &vis)
    {
        vis[node] = 2;

        for (auto it : adj[node])
        {
            if (vis[it] == 1)
            {
                if (dfsCheck(it, adj, vis))
                {
                    return true;
                }
            }
            else if (vis[it] == 2)
            {
                return true;
            }
        }
        vis[node]--;
        return false;
    }
    bool isCyclic(int V, vector<vector<int>> &edges)
    {
        // create adj list
        vector<vector<int>> adj(V);
        for (auto edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
        }

        vector<int> vis(V, 0);

        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
            {
                if (dfsCheck(i, adj, vis))
                {
                    return true;
                }
            }
        }
        return false;
    }

    vector<int> bellmanFord(int V, vector<vector<int>> &edges, int src)
    {
        // Code here
        vector<int> dis(V, 1e8);

        dis[src] = 0;

        for (int i = 0; i < V - 1; i++)
        {
            for (auto it : edges)
            {
                int u = it[0];
                int v = it[1];
                int w = it[2];

                if (dis[u] != 1e8 && dis[u] + w < dis[v])
                {
                    dis[v] = dis[u] + w;
                }
            }
        }

        // find if negative cycle
        for (auto it : edges)
        {
            int u = it[0];
            int v = it[1];
            int w = it[2];

            if (dis[u] != 1e8 && dis[u] + w < dis[v])
            {
                return {-1};
            }
        }
        return dis;
    }

    void countIslandsBFS(int row, int col, vector<vector<char>> &grid, vector<vector<int>> &vis, int n, int m, int dx[], int dy[])
    {
        vis[row][col] == 1;
        queue<pair<int, int>> q;
        q.push({row, col});

        while (!q.empty())
        {
            int cRow = q.front().first;
            int cCol = q.front().second;
            q.pop();
            for (int i = 0; i < 8; i++)
            {
                int nR = cRow + dx[i];
                int nC = cCol + dy[i];
                if (nR >= 0 && nR < n && nC >= 0 && nC < m && grid[nR][nC] == 'L' && !vis[nR][nC])
                {
                    vis[nR][nC] = 1;
                    q.push({nR, nC});
                }
            }
        }
    }
    int countIslands(vector<vector<char>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> vis(n, vector<int>(m, 0));
        int count = 0;
        // 8 directions
        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < m; col++)
            {
                if (!vis[row][col] && grid[row][col] == 'L')
                {
                    count++;
                    countIslandsBFS(row, col, grid, vis, n, m, dx, dy);
                }
            }
        }
        return count;
    }

    int isNegativeWeightCycle(int n, vector<vector<int>> edges)
    {
        vector<int> dist(n, INT_MAX);
        dist[0] = 0;

        // Relax all edges n-1 times
        for (int i = 1; i < n; i++)
        {
            for (auto &edge : edges)
            {
                if (edge.size() < 3)
                    continue;
                int u = edge[0], v = edge[1], wt = edge[2];
                if (dist[u] != INT_MAX && dist[u] + wt < dist[v])
                {
                    dist[v] = dist[u] + wt;
                }
            }
        }

        // Check for negative-weight cycles
        for (auto &edge : edges)
        {
            if (edge.size() < 3)
                continue;
            int u = edge[0], v = edge[1], wt = edge[2];
            if (dist[u] != INT_MAX && dist[u] + wt < dist[v])
            {
                return 1;
            }
        }
        return 0;
    }

    vector<int> dijkstra(int V, vector<vector<int>> &edges, int src)
    {
        vector<pair<int, int>> adj[V];

        for (auto edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});

        while (!pq.empty())
        {
            int dis = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            for (auto it : adj[node])
            {
                int adjNode = it.first;
                int adjWeight = it.second;

                if (adjWeight + dis < dist[adjNode])
                {
                    dist[adjNode] = adjWeight + dis;
                    pq.push({dist[adjNode], adjNode});
                }
            }
        }
        return dist;
    }

    int minStepToReachTarget(vector<int> &knightPos, vector<int> &targetPos, int n)
    {
        queue<pair<pair<int, int>, int>> q;
        q.push({{knightPos[0], knightPos[1]}, 1});

        int dx[] = {};
        int dy[] = {};
        int steps = 0;
        vector<vector<int>> vis(n, vector<int>(n, 0));
        while (!q.empty())
        {
            auto temp = q.front();
            int x = temp.first.first;
            int y = temp.first.second;
            steps = temp.second;
            q.pop();

            if (x == targetPos[0] && y == targetPos[1])
            {
                return steps;
            }

            for (int i = 0; i < 8; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx >= 0 && ny >= 0 && nx < n && ny < n && ny < n && !vis[nx][ny])
                {
                    vis[nx][ny] = 1;
                    q.push({{nx, ny}, steps + 1});
                }
            }
        }
        return -1;
    }
};

class DP
{
public:
    // DP
    void printRecur(int i, int n, vector<int> &arr, vector<int> &ds)
    {
        // base condition
        if (i == n)
        {
            if (ds.size() == 0)
            {
                cout << "{}";
            }
            else
            {
                for (auto a : ds)
                {
                    cout << a << " ";
                }
            }
            cout << endl;
            return;
        }

        printRecur(i + 1, n, arr, ds); // not pick

        ds.push_back(arr[i]);
        printRecur(i + 1, n, arr, ds); // pick
        ds.pop_back();
    }
    void printSubsequence(vector<int> arr)
    {
        int n = arr.size();
        vector<int> ds;
        printRecur(0, n, arr, ds);
    }

    // SUM
    bool printSumRecur(int i, int n, vector<int> &arr, vector<int> &ds, int s, int target)
    {
        // base condition
        if (i == n)
        {
            if (target == s)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        if (printSumRecur(i + 1, n, arr, ds, s, target))
            return true; // not pick

        s += arr[i];
        if (printSumRecur(i + 1, n, arr, ds, s, target))
            return true; // pick
        s -= arr[i];

        return false;
    }
    bool printSubsequenceSum(vector<int> arr, int target)
    {
        int n = arr.size();
        vector<int> ds;
        return printSumRecur(0, n, arr, ds, 0, target);
    }

    // COUNT
    int printCountRecur(int i, int n, vector<int> &arr, int s, int target)
    {
        // base condition
        if (i == n)
        {
            if (target == s)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }

        int l = printCountRecur(i + 1, n, arr, s, target);

        s += arr[i];
        int r = printCountRecur(i + 1, n, arr, s, target);
        s -= arr[i];

        return l + r;
    }
    int printSubsequenceCount(vector<int> arr, int target)
    {
        int n = arr.size();
        return printCountRecur(0, n, arr, 0, target);
    }

    int countWaysRecur(int n, vector<int> &memo)
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

        return memo[n] = countWaysRecur(n - 1, memo) + countWaysRecur(n - 2, memo);
    }
    int countWays(int n)
    {
        vector<int> memo(n + 1, -1);
        return countWaysRecur(n, memo);
    }

    int robRecur(int index, vector<int> &nums, vector<int> &memo)
    {
        if (index == 0)
        {
            return nums[index];
        }
        if (index < 0)
        {
            return 0;
        }
        if (memo[index] != -1)
        {
            return memo[index];
        }
        int even = nums[index] + robRecur(index - 2, nums, memo);
        int odd = 0 + robRecur(index - 1, nums, memo);

        return memo[index] = max(odd, even);
    }
    int rob(vector<int> &nums)
    {
        vector<int> memo(nums.size() + 1, -1);
        return robRecur(nums.size() - 1, nums, memo);
    }

    int robDP(vector<int> &nums)
    {
        vector<int> dp(nums.size() + 1, 0);
        dp[0] = nums[0];
        int take, notTake;
        for (int i = 1; i < nums.size(); i++)
        {

            if (i > 1)
            {
                take += nums[i] + dp[i - 2];
            }
            notTake += 0 + dp[i - 1];
            dp[i] = max(take, notTake);
        }
        return dp[nums.size()];
    }

    int uniquePathsWithObstaclesRecur(int i, int j, vector<vector<int>> &obstacleGrid, vector<vector<int>> &memo)
    {
        if (i == 0 && j == 0)
        {
            return 1;
        }

        if (i < 0 || j < 0)
        {
            return 0;
        }

        if (obstacleGrid[i][j] == 1)
        {
            return 0;
        }
        if (memo[i][j] != -1)
        {
            return memo[i][j];
        }
        int l = uniquePathsWithObstaclesRecur(i - 1, j, obstacleGrid, memo);
        int r = uniquePathsWithObstaclesRecur(i, j - 1, obstacleGrid, memo);

        return memo[i][j] = l + r;
    }
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        int n = obstacleGrid.size() - 1;
        int m = obstacleGrid[0].size() - 1;
        vector<vector<int>> memo(n + 1, vector<int>(m + 1, -1));
        return uniquePathsWithObstaclesRecur(n, m, obstacleGrid, memo);
    }

    int uniquePathsWithObstaclesTb(vector<vector<int>> &obstacleGrid)
    {
        int n = obstacleGrid.size();
        int m = obstacleGrid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (obstacleGrid[i][j] == 1)
                {
                    dp[i][j] = 0;
                }
                else if (i == 0 && j == 0)
                {
                    dp[i][j] = 1;
                }
                else
                {
                    int l = (i > 0) ? dp[i - 1][j] : 0;
                    int r = (j > 0) ? dp[i][j - 1] : 0;
                    dp[i][j] = l + r;
                }
            }
        }

        return dp[n - 1][m - 1];
    }

    int uniquePathsWithObstaclesSo(vector<vector<int>> &obstacleGrid)
    {
        int n = obstacleGrid.size();
        int m = obstacleGrid[0].size();
        vector<int> prev(m, 0);

        for (int i = 0; i < n; i++)
        {
            vector<int> temp(m, 0);
            for (int j = 0; j < m; j++)
            {
                if (obstacleGrid[i][j] == 1)
                {
                    temp[j] = 0;
                }
                else if (i == 0 && j == 0)
                {
                    temp[j] = 1;
                }
                else
                {
                    int l = (i > 0) ? prev[j] : 0;
                    int r = (j > 0) ? temp[j - 1] : 0;
                    temp[j] = l + r;
                }
            }
            prev = temp;
        }

        return prev[m - 1];
    }

    int countWays2Recur(int n)
    {
        if (n == 0)
        {
            return 1;
        }
        if (n < 0)
        {
            return 0;
        }

        return countWays2Recur(n - 1) + countWays2Recur(n - 2);
    }

    int countWays2(int n)
    {
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            dp[i] += dp[i - 1];
            if (i > 1)
            {
                dp[i] += dp[i - 2];
            }
        }
        return dp[n];
    }

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
        vector<vector<int>> memo(n, vector<int>(m, -1));
        int res = numberOfPathsRecurMemo(memo, m - 1, n - 1);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << memo[i][j];
            }
        }
        return res;
    }

    // printing the tables

    int countPathsRec(int i, int j, int m, int n)
    {
        if (i == m - 1 && j == n - 1)
            return 1; // reached destination
        if (i >= m || j >= n)
            return 0; // out of bounds

        int right = countPathsRec(i, j + 1, m, n);
        int down = countPathsRec(i + 1, j, m, n);
        return right + down;
    }

    int countPathsMemo(int i, int j, int m, int n, vector<vector<int>> &dp)
    {
        if (i == m - 1 && j == n - 1)
            return 1;
        if (i >= m || j >= n)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j]; // already computed

        int right = countPathsMemo(i, j + 1, m, n, dp);
        int down = countPathsMemo(i + 1, j, m, n, dp);

        return dp[i][j] = right + down;
    }

    // dp table (after computation):
    // [6, 3, 1]
    // [3, 2, 1]
    // [1, 1, 0]

    int countPathsTab(int m, int n)
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

        // print dp table
        cout << "Tabulation DP table:\n";
        for (auto &row : dp)
        {
            for (int x : row)
                cout << x << " ";
            cout << "\n";
        }
        return dp[m - 1][n - 1];
    }

    // Tabulation DP:
    // 1 1 1
    // 1 2 3
    // 1 3 6

    int countPathsSpace(int m, int n)
    {
        vector<int> prev(n, 0);

        for (int i = 0; i < m; i++)
        {
            vector<int> curr(n, 0);
            for (int j = 0; j < n; j++)
            {
                if (i == 0 && j == 0)
                    curr[j] = 1;
                else
                {
                    int up = (i > 0) ? prev[j] : 0;
                    int left = (j > 0) ? curr[j - 1] : 0;
                    curr[j] = up + left;
                }
            }

            prev = curr;

            // print row by row
            cout << "Row " << i << ": ";
            for (int x : prev)
                cout << x << " ";
            cout << "\n";
        }
        return prev[n - 1];
    }

    // Row 0: 1 1 1
    // Row 1: 1 2 3
    // Row 2: 1 3 6

    // ans:
    // Recursion: 6
    // Memoization: 6
    // Tabulation DP table:
    // 1 1 1
    // 1 2 3
    // 1 3 6
    // Tabulation: 6
    // Row 0: 1 1 1
    // Row 1: 1 2 3
    // Row 2: 1 3 6
    // Space Optimized: 6

    // end printing tables

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
    int minPathSumTb(vector<vector<int>> &grid)
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

        // print dp table
        cout << "Tabulation DP table:\n";
        for (auto &row : dp)
        {
            for (int x : row)
                cout << x << " ";
            cout << "\n";
        }

        return dp[n - 1][m - 1];
    }

    int maximumPathRecur(int i, int j, vector<vector<int>> &mat, int n, int m)
    {
        if (i < 0 || j < 0 || j >= m)
        {
            return INT_MIN;
        }
        if (i == 0)
        {
            return mat[i][j];
        }
        int upLeft = maximumPathRecur(i - 1, j - 1, mat, n, m);
        int up = maximumPathRecur(i - 1, j, mat, n, m);
        int upRight = maximumPathRecur(i - 1, j + 1, mat, n, m);

        return mat[i][j] + max({upLeft, up, upRight});
    }
    int maximumPath(vector<vector<int>> &mat)
    {
        int n = mat.size();
        int m = mat[0].size();

        int res = INT_MIN;
        for (int j = 0; j < m; j++)
        {
            res = max(res, maximumPathRecur(n - 1, j, mat, n, m));
        }
        return res;
    }
    int maximumPathTb(vector<vector<int>> &mat)
    {
        int n = mat.size();
        int m = mat[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));

        for (int j = 0; j < m; j++)
        {
            dp[0][j] = mat[0][j];
        }

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int upLeft = (i > 0 && j > 0) ? dp[i - 1][j - 1] : INT_MIN;
                int up = (i > 0) ? dp[i - 1][j] : INT_MIN;
                int upRight = (i > 0 && j + 1 < m) ? dp[i - 1][j + 1] : INT_MIN;

                dp[i][j] = mat[i][j] + max({upLeft, up, upRight});
            }
        }

        int result = INT_MIN;
        for (int j = 0; j < m; ++j)
        {
            result = max(result, dp[n - 1][j]);
        }
        return result;
    }
    int maximumPathSo(vector<vector<int>> &mat)
    {
        int n = mat.size();
        int m = mat[0].size();
        vector<int> prev(m, 0);

        // Initialize prev with the first row of mat
        for (int j = 0; j < m; j++)
        {
            prev[j] = mat[0][j];
        }

        for (int i = 1; i < n; i++)
        {
            vector<int> curr(m, 0);
            for (int j = 0; j < m; j++)
            {
                int upLeft = (j > 0) ? prev[j - 1] : INT_MIN;
                int up = prev[j];
                int upRight = (j + 1 < m) ? prev[j + 1] : INT_MIN;

                curr[j] = mat[i][j] + max({upLeft, up, upRight});
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

    int minimumTotalRecur(int i, int j, int n, int m, vector<vector<int>> &triangle)
    {
        if (i == n - 1)
        {
            return triangle[i][j];
        }

        int d = minimumTotalRecur(i + 1, j, n, m, triangle);
        int dg = minimumTotalRecur(i + 1, j + 1, n, m, triangle);

        return triangle[i][j] + min(d, dg);
    }
    int minimumTotal(vector<vector<int>> &triangle)
    {
        int n = triangle.size();
        int m = triangle[0].size();

        return minimumTotalRecur(0, 0, n, m, triangle);
    }

    long long numberOfPathRecur(int i, int j, int n, int k, vector<vector<int>> &arr)
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

        int left = numberOfPathRecur(i - 1, j, n, k - arr[i][j], arr);
        int up = numberOfPathRecur(i, j - 1, n, k - arr[i][j], arr);
        return left + up;
    }
    long long numberOfPath(int n, int k, vector<vector<int>> &arr)
    {

        return numberOfPathRecur(n - 1, n - 1, n, k, arr);
    }
    long long numberOfPathTb(int n, int k, vector<vector<int>> &arr)
    {
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int left = (i > 0) ? dp[i - 1][j] : 0;
                int up = (j > 0) ? dp[i][j - 1] : 0;
                dp[i][j] = left + up;
            }
        }
        return dp[n - 1][n - 1];
    }

    int minFallingPathSumRecur(int i, int j, int m, vector<vector<int>> &matrix, vector<vector<int>> &memo)
    {
        if (j < 0 || j >= m)
        {
            return INT_MAX;
        }
        if (i == 0)
        {
            return matrix[i][j];
        }
        if (memo[i][j] != -1)
        {
            return memo[i][j];
        }
        int leftD = minFallingPathSumRecur(i - 1, j - 1, m, matrix, memo);
        int up = minFallingPathSumRecur(i - 1, j, m, matrix, memo);
        int rightD = minFallingPathSumRecur(i - 1, j + 1, m, matrix, memo);

        return memo[i][j] = matrix[i][j] + min({leftD, up, rightD});
    }
    int minFallingPathSum(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        int m = matrix[0].size();
        int result = INT_MAX;
        vector<vector<int>> memo(n, vector<int>(m, -1));
        for (int j = 0; j < m; j++)
        {
            result = min(result, minFallingPathSumRecur(n - 1, j, m, matrix, memo));
        }
        return result;
    }
    int minFallingPathSumTb(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (i == 0)
                {
                    dp[0][j] = matrix[0][j];
                }
                else
                {
                    int leftD = (j > 0) ? dp[i - 1][j - 1] : INT_MAX;
                    int up = dp[i - 1][j];
                    int rightD = (j + 1 < m) ? dp[i - 1][j + 1] : INT_MAX;

                    dp[i][j] = matrix[i][j] + min({leftD, up, rightD});
                }
            }
        }

        // print dp table
        cout << "Tabulation DP table:\n";
        for (auto &row : dp)
        {
            for (int x : row)
                cout << x << " ";
            cout << "\n";
        }
        int result = INT_MAX;
        for (int k = 0; k < m; k++)
        {
            result = min(result, dp[n - 1][k]);
        }
        return result;
    }
    int minFallingPathSumSo(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<int> prev(m, 0);

        for (int i = 0; i < n; i++)
        {
            vector<int> curr(m, 0);
            for (int j = 0; j < m; j++)
            {
                if (i == 0)
                {
                    curr[j] = matrix[0][j];
                }
                else
                {
                    int leftD = (j > 0) ? prev[j - 1] : INT_MAX;
                    int up = prev[j];
                    int rightD = (j + 1 < m) ? prev[j + 1] : INT_MAX;

                    curr[j] = matrix[i][j] + min({leftD, up, rightD});
                }
            }
            prev = curr;
        }

        int result = INT_MAX;
        for (int k = 0; k < m; k++)
        {
            result = min(result, prev[k]);
        }
        return result;
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

        int notTake = isSubsetSumRecur(i - 1, arr, sum);
        int take = false;
        if (sum <= arr[i])
        {
            take = isSubsetSumRecur(i - 1, arr, sum - arr[0]);
        }
        return take || notTake;
    }
    bool isSubsetSum(vector<int> &arr, int sum)
    {
        int n = arr.size();
        return isSubsetSumRecur(n - 1, arr, sum);
    }
    bool isSubsetSumTb(vector<int> &arr, int sum)
    {
        int n = arr.size();
        vector<vector<bool>> dp(n, vector<bool>(sum + 1, false));

        // Initialize first column as true (sum 0 is always possible)
        for (int i = 0; i < n; i++)
        {
            dp[i][0] = true;
        }
        // Initialize first row
        if (arr[0] <= sum)
        {
            dp[0][arr[0]] = true;
        }

        for (int i = 1; i < n; i++)
        {
            for (int s = 1; s <= sum; s++)
            {
                bool notTake = dp[i - 1][s];
                bool take = false;
                if (arr[i] <= s)
                {
                    take = dp[i - 1][s - arr[i]];
                }
                dp[i][s] = take || notTake;
            }
        }
        return dp[n - 1][sum];
    }

    int perfectSumRecur(int i, vector<int> &arr, int target)
    {
        if (target == 0)
        {
            return 1;
        }

        if (i == 0)
        {
            return arr[0] == target;
        }

        int notTake = perfectSumRecur(i - 1, arr, target);
        int take = 0;
        if (arr[i] <= target)
        {
            take = perfectSumRecur(i - 1, arr, target - arr[i]);
        }

        return notTake + take;
    }
    int perfectSum(vector<int> &arr, int target)
    {
        int n = arr.size();
        return perfectSumRecur(n - 1, arr, target);
    }
    int perfectSumTb(vector<int> &arr, int target)
    {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(target + 1, 0));

        for (int i = 0; i < n; i++)
        {
            dp[i][0] = 1;
        }

        if (arr[0] <= target)
        {
            dp[0][arr[0]] = 1;
        }

        for (int i = 1; i < n; i++)
        {
            for (int tar = 1; tar <= target; tar++)
            {
                int notTake = dp[i - 1][tar];
                int take = 0;
                if (arr[i] <= tar)
                {
                    take = dp[i - 1][tar - arr[i]];
                }

                dp[i][tar] = notTake + take;
            }
        }
        // print dp table
        cout << "Tabulation DP table:\n";
        for (auto &row : dp)
        {
            for (int x : row)
                cout << x << " ";
            cout << "\n";
        }
        return dp[n - 1][target];
    }

    bool equalPartition(vector<int> &arr)
    {
        int n = arr.size();
        int totalSum = accumulate(arr.begin(), arr.end(), 0);
        if (totalSum % 2)
        {
            return false;
        }
        int target = totalSum / 2;
        return isSubsetSumTb(arr, target);
    }

    int knapsackRecur(int i, vector<int> &val, vector<int> &wt, int W, vector<vector<int>> &memo)
    {
        if (i == 0)
        {
            if (wt[i] <= W)
            {
                return val[0];
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
        int notTake = 0 + knapsackRecur(i - 1, val, wt, W, memo);
        int take = INT_MIN;
        if (wt[i] <= W)
        {
            take = val[i] + knapsackRecur(i - 1, val, wt, W - wt[i], memo);
        }
        return memo[i][W] = max(notTake, take);
    }
    int knapsack(int W, vector<int> &val, vector<int> &wt)
    {
        int n = val.size();
        vector<vector<int>> memo(n, vector<int>(W + 1, -1));
        return knapsackRecur(n - 1, val, wt, W, memo);
    }
    int knapsackTb(int W, vector<int> &val, vector<int> &wt)
    {
        int n = val.size();
        vector<vector<int>> dp(n, vector<int>(W + 1, 0));

        for (int wi = wt[0]; wi <= W; wi++)
        {
            dp[0][wi] = val[0];
        }

        for (int i = 1; i < n; i++)
        {
            for (int wi = 0; wi <= W; wi++)
            {
                int notTake = 0 + dp[i - 1][wi];
                int take = INT_MIN;
                if (wt[i] <= wi)
                {
                    take = val[i] + dp[i - 1][wi - wt[i]];
                }
                dp[i][wi] = max(notTake, take);
            }
        }
        // print dp table
        cout << "Tabulation DP table:\n";
        for (auto &row : dp)
        {
            for (int x : row)
                cout << x << " ";
            cout << "\n";
        }
        return dp[n - 1][W];
    }
    int knapsackSo(int W, vector<int> &val, vector<int> &wt)
    {
        int n = val.size();
        vector<int> prev(W + 1, 0);
        vector<int> curr(W + 1, 0);

        for (int we = wt[0]; we <= W; we++)
        {
            prev[we] = val[0];
        }

        for (int i = 1; i < n; i++)
        {
            for (int wi = 0; wi <= W; wi++)
            {
                int notTake = 0 + prev[wi];
                int take = INT_MIN;
                if (wt[i] <= wi)
                {
                    take = val[i] + prev[wi - wt[i]];
                }
                curr[wi] = max(notTake, take);
            }
            prev = curr;
        }
        return prev[W];
    }

    int findMaxSumRecur(int i, vector<int> &arr)
    {
        if (i == 0)
        {
            return arr[0];
        }

        if (i < 0)
        {
            return INT_MIN;
        }

        int notTake = 0 + findMaxSumRecur(i - 1, arr);
        int take = arr[i] + findMaxSumRecur(i - 2, arr);

        return max(notTake, take);
    }
    int findMaxSum(vector<int> &arr)
    {
        int n = arr.size();
        return findMaxSumRecur(n - 1, arr);
    }
    int findMaxSumTb(vector<int> &arr)
    {
        int n = arr.size();
        vector<int> dp(n, 0);

        for (int i = 0; i < n; i++)
        {
            if (i == 0)
            {
                dp[0] = arr[0];
            }
            int notTake = (i > 0) ? 0 + dp[i - 1] : INT_MIN;
            int take = arr[i];
            if (i > 1)
            {
                take += dp[i - 2];
            }

            dp[i] = max(notTake, take);
        }
        return dp[n - 1];
    }
    int findMaxSumSo(vector<int> &arr)
    {
        int n = arr.size();
        int prev2 = 0;
        int prev = arr[0];
        int curr = 0;

        for (int i = 1; i < n; i++)
        {
            int notTake = prev;
            int take = arr[i] + prev2;

            curr = max(notTake, take);
            prev2 = prev;
            prev = curr;
        }
        return prev;
    }

    int countRecur(int i, vector<int> &coins, int sum)
    {
        if (i == 0)
        {
            return (sum % coins[0] == 0);
        }
        if (i < 0)
        {
            return 0;
        }

        int notTake = countRecur(i - 1, coins, sum);
        int take = 0;
        if (coins[i] <= sum)
        {
            take = countRecur(i, coins, sum - coins[i]);
        }

        return notTake + take;
    }
    int count(vector<int> &coins, int sum)
    {
        int n = coins.size();
        return countRecur(n - 1, coins, sum);
    }
    int countTb(vector<int> &coins, int sum)
    {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(sum + 1, 0));

        for (int s = 1; s <= sum; s++)
        {
            dp[0][s] = s % coins[0] == 0;
        }

        for (int i = 1; i < n; i++)
        {
            for (int su = 0; su <= sum; su++)
            {
                int notTake = dp[i - 1][su];
                int take = 0;
                if (coins[i] <= su)
                {
                    take = dp[i][su - coins[i]];
                }

                dp[i][su] = notTake + take;
            }
        }

        return dp[n - 1][sum];
    }
    int countSo(vector<int> &coins, int sum)
    {
        int n = coins.size();
        vector<int> prev(n, 0);
        vector<int> curr(sum + 1, 0);

        for (int s = 1; s <= sum; s++)
        {
            prev[s] = s % coins[0] == 0;
        }

        for (int i = 1; i < n; i++)
        {
            for (int su = 0; su <= sum; su++)
            {
                int notTake = prev[su];
                int take = 0;
                if (coins[i] <= su)
                {
                    take = curr[su - coins[i]];
                }

                curr[su] = notTake + take;
            }
            prev = curr;
        }

        return prev[sum];
    }

    int minCoinsRecur(int i, vector<int> &coins, int sum)
    {
        if (i == 0)
        {
            if (sum % coins[0] == 0)
            {
                return sum / coins[0];
            }
            else
            {
                return INT_MAX;
            }
        }

        int notTake = minCoinsRecur(i - 1, coins, sum);
        int take = 0;
        if (coins[i] <= sum)
        {
            take = 1 + minCoinsRecur(i, coins, sum - coins[i]);
        }

        return min(notTake, take);
    }
    int minCoins(vector<int> &coins, int sum)
    {
        int n = coins.size();
        return minCoinsRecur(n - 1, coins, sum);
    }
    int minCoinsTb(vector<int> &coins, int sum)
    {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(sum + 1, 0));
        for (int s = 0; s <= sum; s++)
        {
            if (s % coins[0] == 0)
            {
                dp[0][s] = s / coins[0];
            }
            else
            {
                dp[0][s] = INT_MAX;
            }
        }

        for (int i = 1; i < n; i++)
        {
            for (int su = 0; su <= sum; su++)
            {
                int notTake = dp[i - 1][su];
                int take = 0;
                if (coins[i] <= su)
                {
                    take = 1 + dp[i][su - coins[i]];
                }

                dp[i][su] = min(notTake, take);
            }
        }
        return dp[n - 1][sum];
    }
    int minCoinsSo(vector<int> &coins, int sum)
    {
        int n = coins.size();
        vector<int> prev(sum + 1, 0);
        for (int s = 0; s <= sum; s++)
        {
            if (s % coins[0] == 0)
            {
                prev[s] = s / coins[0];
            }
            else
            {
                prev[s] = INT_MAX;
            }
        }

        for (int i = 1; i < n; i++)
        {
            vector<int> curr(sum + 1, 0);
            for (int su = 0; su <= sum; su++)
            {
                int notTake = prev[su];
                int take = INT_MAX;
                if (coins[i] <= su && prev[su - coins[i]] != INT_MAX)
                {
                    take = 1 + curr[su - coins[i]];
                }
                curr[su] = min(notTake, take);
            }
            prev = curr;
        }
        return (prev[sum] == INT_MAX) ? -1 : prev[sum];
    }

    int cutRodRecur(int i, vector<int> &price, int n)
    {
        if (i == 0)
        {
            return n * price[0];
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
    int cutRodTb(vector<int> &price)
    {
        int n = price.size();
        vector<vector<int>> dp(n, vector<int>(n + 1, 0));
        for (int N = 0; N <= n; N++)
        {
            dp[0][N] = N * price[0];
        }

        for (int i = 1; i < n; i++)
        {
            for (int N = 0; N <= n; N++)
            {
                int notTake = 0 + dp[i - 1][N];
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

    int minimumCostRecur(int i, int n, int w, vector<int> &cost)
    {
        if (w == 0)
        {
            return 0;
        }

        if (i < 0)
        {
            return 1e9;
        }

        int notTake = minimumCostRecur(i - 1, n, w, cost);
        int take = INT_MAX;
        int package = i + 1;
        if (cost[i] != -1 && package <= w)
        {
            take = cost[i] + minimumCostRecur(i, n, w - package, cost);
        }

        return min(notTake, take);
    }
    int minimumCost(int n, int w, vector<int> &cost)
    {
        return minimumCostRecur(n - 1, n, w, cost);
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
            else
            {
                return 0;
            }
        }

        int notTake = knapSackRecur(i - 1, val, wt, capacity);
        int take = INT_MIN;
        if (wt[i] <= capacity)
        {
            take = val[i] + knapSackRecur(i, val, wt, capacity - wt[i]);
        }
        return max(notTake, take);
    }
    int knapSack2(vector<int> &val, vector<int> &wt, int capacity)
    {
        int n = val.size();
        return knapSackRecur(n - 1, val, wt, capacity);
    }
    int knapSack2Tb(vector<int> &val, vector<int> &wt, int capacity)
    {
        int n = val.size();
        vector<vector<int>> dp(n, vector<int>(capacity + 1, 0));

        for (int cap = 0; cap <= capacity; cap++)
        {
            dp[0][cap] = (cap / wt[0]) * val[0];
        }

        for (int i = 1; i < n; i++)
        {
            for (int cap = 0; cap <= capacity; cap++)
            {
                int notTake = dp[i - 1][cap];
                int take = 0;
                if (wt[i] <= cap)
                {
                    take = val[i] + dp[i][cap - wt[i]];
                }
                dp[i][cap] = max(notTake, take);
            }
        }
        // print dp table
        cout << "Tabulation DP table:\n";
        for (auto &row : dp)
        {
            for (int x : row)
                cout << x << " ";
            cout << "\n";
        }
        return dp[n - 1][capacity];
    }
    int knapSack2So(vector<int> &val, vector<int> &wt, int capacity)
    {
        int n = val.size();
        vector<int> prev(n, 0), curr(capacity + 1, 0);

        for (int cap = 0; cap <= capacity; cap++)
        {
            prev[cap] = (cap / wt[0]) * val[0];
        }

        for (int i = 1; i < n; i++)
        {
            for (int cap = 0; cap <= capacity; cap++)
            {
                int notTake = prev[cap];
                int take = INT_MIN;
                if (wt[i] <= cap)
                {
                    take = val[i] + curr[cap - wt[i]];
                }
                curr[cap] = max(notTake, take);
            }
            prev = curr;
        }
        return prev[capacity];
    }

    int lengthOfLISRecur(int i, int n, vector<int> &nums, int prev_ind, vector<vector<int>> &memo)
    {
        if (i == n)
        {
            return 0;
        }
        if (memo[i][prev_ind + 1] != -1)
        {
            return memo[i][prev_ind + 1];
        }
        int len = 0 + lengthOfLISRecur(i + 1, n, nums, prev_ind, memo);
        if (prev_ind == -1 || nums[i] > nums[prev_ind])
        {
            len = max(len, 1 + lengthOfLISRecur(i + 1, n, nums, i, memo));
        }
        return memo[i][prev_ind + 1] = len;
    }
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<vector<int>> memo(n, vector<int>(n + 1, -1));
        return lengthOfLISRecur(0, n, nums, -1, memo);
    }
    int lengthOfLISTb(vector<int> &nums)
    {
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int i = n - 1; i >= 0; i--)
        {
            for (int prev_ind = i - 1; prev_ind >= -1; prev_ind--)
            {
                int len = 0 + dp[i + 1][prev_ind + 1];
                if (prev_ind == -1 || nums[i] > nums[prev_ind])
                {
                    len = max(len, 1 + dp[i + 1][i + 1]);
                }
                dp[i][prev_ind + 1] = len;
            }
        }
        return dp[0][-1 + 1];
    }

    // DP on string
    int longestCommonSubsequenceRecur(int i, int j, string text1, string text2, vector<vector<int>> &memo)
    {
        if (i < 0 || j < 0)
        {
            return 0;
        }
        if (memo[i][j] != -1)
        {
            return memo[i][j];
        }
        if (text1[i] == text2[j])
        {
            return 1 + longestCommonSubsequenceRecur(i - 1, j - 1, text1, text2, memo);
        }
        return memo[i][j] = 0 + max(longestCommonSubsequenceRecur(i - 1, j, text1, text2, memo), longestCommonSubsequenceRecur(i, j - 1, text1, text2, memo));
    }
    int longestCommonSubsequence(string text1, string text2)
    {
        int n = text1.size();
        int m = text2.size();
        vector<vector<int>> memo(n, vector<int>(m, -1));
        return longestCommonSubsequenceRecur(n - 1, m - 1, text1, text2, memo);
    }
    int longestCommonSubsequenceTb(string text1, string text2)
    {
        int n = text1.size();
        int m = text2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = 0;
        }
        for (int j = 0; j <= m; j++)
        {
            dp[0][j] = 0;
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
                    dp[i][j] = 0 + max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        // Print dp table
        cout << "Tabulation DP table:\n";
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= m; j++)
            {
                cout << dp[i][j] << " ";
            }
            cout << "\n";
        }
        return dp[n][m];
    }
    int longestCommonSubsequenceSo(string text1, string text2)
    {
        int n = text1.size();
        int m = text2.size();
        vector<int> prev(n + 1, 0);
        vector<int> curr(m + 1, 0);

        for (int i = 0; i <= n; i++)
        {
            prev[0] = 0;
        }

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
                    curr[j] = 0 + max(prev[j], curr[j - 1]);
                }
            }
            prev = curr;
        }

        return prev[m];
    }

    int longestPalindromeSubseq(string s)
    {
        string originalString = s;
        reverse(s.begin(), s.end());
        return longestCommonSubsequenceSo(originalString, s);
    }

    int minInsertions(string s)
    {
        int totalStringSize = s.size();
        string originalString = s;
        reverse(s.begin(), s.end());
        int lcsLength = longestCommonSubsequenceSo(originalString, s);
        return totalStringSize - lcsLength;
    }

    int minOperations(string &s1, string &s2)
    {
        int s1Size = s1.size();
        int s2Size = s2.size();
        int lcsLength = longestCommonSubsequenceSo(s1, s2);
        int ans = (s1Size - lcsLength) + (s2Size - lcsLength);
        return ans;
    }

    int shortestCommonSupersequence(string &s1, string &s2)
    {
        int s1Size = s1.size();
        int s2Size = s2.size();
        int lcsLength = longestCommonSubsequenceSo(s1, s2);
        int balanceStringSize = s2Size - lcsLength;
        return s1Size + balanceStringSize;
    }

    int longestCommonSubstr(string &s1, string &s2)
    {
        int n = s1.size();
        int m = s2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        int ans = 0;
        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = 0;
        }
        for (int j = 0; j <= m; j++)
        {
            dp[0][j] = 0;
        }

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
                    dp[i][j] = 0;
                }
            }
        }
        // Print dp table
        cout << "Tabulation DP table:\n";
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= m; j++)
            {
                cout << dp[i][j] << " ";
            }
            cout << "\n";
        }
        return ans;
    }

    int editDistanceRecur(int i, int j, string &s1, string &s2, vector<vector<int>> &memo)
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
            return 0 + editDistanceRecur(i - 1, j - 1, s1, s2, memo);
        }
        return memo[i][j] = 1 + min({editDistanceRecur(i, j - 1, s1, s2, memo), editDistanceRecur(i - 1, j, s1, s2, memo), editDistanceRecur(i - 1, j - 1, s1, s2, memo)});
    }
    int editDistance(string &s1, string &s2)
    {
        int n = s1.size();
        int m = s2.size();
        vector<vector<int>> memo(n, vector<int>(m, -1));
        return editDistanceRecur(n - 1, m - 1, s1, s2, memo);
    }
    int editDistanceTb(string &s1, string &s2)
    {
        int n = s1.size();
        int m = s2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int j = 0; j <= m; j++)
        {
            dp[0][j] = j;
        }
        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = i;
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (s1[i] == s2[j])
                {
                    dp[i][j] = 0 + dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = 1 + min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]});
                }
            }
        }
        // print dp table
        cout << "Tabulation DP table:\n";
        for (auto &row : dp)
        {
            for (int x : row)
                cout << x << " ";
            cout << "\n";
        }
        return dp[n][m];
    }
    int editDistanceSo(string &s1, string &s2)
    {
        int n = s1.size();
        int m = s2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        vector<int> prev(n + 1, 0);
        vector<int> curr(m + 1, 0);
        for (int j = 0; j <= m; j++)
        {
            prev[j] = j;
        }

        for (int i = 1; i <= n; i++)
        {
            curr[0] = i;
            for (int j = 1; j <= m; j++)
            {
                if (s1[i - 1] == s2[j - 1])
                {
                    prev[j] = 0 + prev[j - 1];
                }
                else
                {
                    curr[j] = 1 + min({curr[j - 1], prev[j], prev[j - 1]});
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
        else if (i < 0)
        {
            return 0;
        }
        if (txt[i] == pat[j])
        {
            return subseqCountRecur(i - 1, j - 1, txt, pat) + subseqCountRecur(i - 1, j, txt, pat);
        }

        return subseqCountRecur(i - 1, j, txt, pat);
    }
    int subseqCount(string &txt, string &pat)
    {
        int n = txt.size();
        int m = pat.size();
        return subseqCountRecur(n - 1, m - 1, txt, pat);
    }
    int subseqCountTb(string &txt, string &pat)
    {
        int n = txt.size();
        int m = pat.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = 1;
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (txt[i - 1] == pat[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                }
                else
                {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n][m];
    }
    int subseqCountSo(string &txt, string &pat)
    {
        int n = txt.size();
        int m = pat.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        vector<int> prev(n + 1, 0);
        vector<int> curr(m + 1, 0);

        for (int i = 0; i <= n; i++)
        {
            prev[0] = 1;
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (txt[i - 1] == pat[j - 1])
                {
                    curr[j] = prev[j - 1] + prev[j];
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

    bool wildCardecur(int i, int j, string &txt, string &pat)
    {
        if (i < 0 && j < 0)
        {
            return true;
        }
        if (i < 0 && j >= 0)
        {
            return false;
        }
        if (i >= 0 && j < 0)
        {
            for (int k = 0; k <= i; k++)
            {
                if (pat[k] != '*')
                {
                    return false;
                }
            }
            return true;
        }

        if (txt[i] == pat[j] || pat[i] == '?')
        {
            return wildCardecur(i - 1, j - 1, txt, pat);
        }
        else if (pat[j] == '*')
        {
            return wildCardecur(i - 1, j, txt, pat) || wildCardecur(i, j - 1, txt, pat);
        }
        return false;
    }
    bool wildCard(string &txt, string &pat)
    {
        int n = txt.size();
        int m = pat.size();
        return wildCardecur(n - 1, m - 1, txt, pat);
    }

    // DP on stocks
    int maxProfit(vector<int> &prices)
    {
        int mini = prices[0], profit = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            int cost = prices[i] - mini;
            profit = max(profit, cost);
            mini = min(mini, prices[i]); // remembaring the past so it is DP
        }
        return profit;
    }

    int maxProfit2(vector<int> &prices)
    {
        int mini = prices[0], profit = 0;
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
    int maxProfit2Re(int i, int n, vector<int> &prices, int buy, vector<vector<int>> &memo)
    {
        if (i == n)
        {
            return 0;
        }
        int profit = 0;
        if (memo[i][buy] != -1)
        {
            return memo[i][buy];
        }
        if (buy)
        {
            profit = max(-prices[i] + maxProfit2Re(i + 1, n, prices, 0, memo), 0 + maxProfit2Re(i + 1, n, prices, 1, memo));
        }
        else
        {
            profit = max(prices[i] + maxProfit2Re(i + 1, n, prices, 1, memo), maxProfit2Re(i + 1, n, prices, 0, memo));
        }
        return memo[i][buy] = profit;
    }
    int maxProfit2Rec(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> memo(n, vector<int>(2, -1));
        return maxProfit2Re(0, n, prices, 1, memo);
    }
    int maxProfit2Tb(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, -1));
        dp[n][0] = dp[n][1] = 0;
        int profit = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            for (int buy = 0; buy <= 1; buy++)
            {
                if (buy)
                {
                    profit = max(-prices[i] + dp[i + 1][0], dp[i + 1][1]);
                }
                else
                {
                    profit = max(prices[i] + dp[i + 1][1], dp[i + 1][0]);
                }
                dp[i][buy] = profit;
            }
        }
        // print dp table
        cout << "Tabulation DP table:\n";
        for (auto &row : dp)
        {
            for (int x : row)
                cout << x << " ";
            cout << "\n";
        }
        return dp[0][1];
    }
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
        aheadNotBuy = aheadBuy = 0;
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

    int maxProfit3Re(int ind, int n, vector<int> &prices, int buy, vector<vector<vector<int>>> &memo, int cap)
    {
        if (cap == 0)
        {
            return 0;
        }
        if (ind == n)
        {
            return 0;
        }
        if (memo[ind][buy][cap] != -1)
        {
            return memo[ind][buy][cap];
        }
        if (buy)
        {
            return memo[ind][buy][cap] = max(-prices[ind] + maxProfit3Re(ind + 1, n, prices, 0, memo, cap),
                                             0 + maxProfit3Re(ind + 1, n, prices, 1, memo, cap));
        }
        else
        {
            return memo[ind][buy][cap] = max(prices[ind] + maxProfit3Re(ind + 1, n, prices, 1, memo, cap - 1),
                                             0 + maxProfit3Re(ind + 1, n, prices, 0, memo, cap));
        }
    }
    int maxProfit3(vector<int> &prices)
    {
        int n = prices.size();
        int cap = 2;
        vector<vector<vector<int>>> memo(n, vector<vector<int>>(2, vector<int>(3, -1)));
        return maxProfit3Re(0, n, prices, 1, memo, cap);
    }
    int maxProfit3Tb(vector<int> &prices)
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
    int maxProfit3So(vector<int> &prices)
    {
        int n = prices.size();
        int cap = 2;
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));
        vector<vector<int>> after(3, vector<int>(3, 0));
        vector<vector<int>> curr(3, vector<int>(3, 0));

        for (int ind = n - 1; ind >= 0; ind--)
        {
            for (int buy = 0; buy <= 1; buy++)
            {
                for (int cap = 1; cap <= 2; cap++)
                {
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
                after = curr;
            }
        }
        return after[1][2];
    }

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
    int maxProfit4(int k, vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> memo(n, vector<int>(2 * k, -1));
        return maxProfit4RecurTranNumMemo(0, n, k, prices, 0, memo);
    }
    int maxProfit4Tb(int k, vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2 * k, 0));

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
    int maxProfit4So(int k, vector<int> &prices)
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

    int maxProfit5Re(int i, int n, vector<int> &prices, int buy, vector<vector<int>> &memo)
    {
        if (i >= n)
        {
            return 0;
        }

        int profit = 0;
        if (memo[i][buy] != -1)
        {
            return memo[i][buy];
        }
        if (buy)
        {
            profit = max(-prices[i] + maxProfit5Re(i + 1, n, prices, 0, memo), 0 + maxProfit5Re(i + 1, n, prices, 1, memo));
        }
        else
        {
            profit = max(prices[i] + maxProfit5Re(i + 2, n, prices, 1, memo), maxProfit5Re(i + 1, n, prices, 0, memo));
        }
        return memo[i][buy] = profit;
    }
    int maxProfit5(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> memo(n, vector<int>(2, -1));
        return maxProfit5Re(0, n, prices, 1, memo);
    }
    int maxProfit5Dp(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n + 2, vector<int>(2, 0));

        for (int i = n - 1; i >= 0; i--)
        {
            dp[i][1] = max(-prices[i] + dp[i + 1][0], dp[i + 1][1]);

            dp[i][0] = max(prices[i] + dp[i + 2][1], dp[i + 1][0]);
        }
        // print dp table
        cout << "Tabulation DP table:\n";
        for (auto &row : dp)
        {
            for (int x : row)
                cout << x << " ";
            cout << "\n";
        }
        return dp[0][1];
    }

    int maxProfit6Recur(int i, int n, vector<int> &prices, int buy, int fee)
    {
        if (i == n)
        {
            return 0;
        }

        if (buy)
        {
            return max(-prices[i] + maxProfit6Recur(i + 1, n, prices, 0, fee), 0 + maxProfit6Recur(i + 1, n, prices, 1, fee));
        }
        else
        {
            return max((prices[i] - fee) + maxProfit6Recur(i + 1, n, prices, 1, fee), 0 + maxProfit6Recur(i + 1, n, prices, 0, fee));
        }
    }
    int maxProfit6(vector<int> &prices, int fee)
    {
        int n = prices.size();
        return maxProfit6Recur(0, n, prices, 1, fee);
    }
};
int main()
{
    Revision r;
    vector<vector<int>> arr = {{2, 1, 3}, {6, 5, 4}, {7, 8, 9}};
    string s = "3[b2[ca]]";
    int arr1[] = {2, 1, 2};

    vector<vector<char>> grid = {{'L', 'L', 'W', 'W', 'W'}, {'W', 'L', 'W', 'W', 'L'}, {'L', 'W', 'W', 'L', 'L'}, {'W', 'W', 'W', 'W', 'W'}, {'L', 'W', 'L', 'L', 'W'}};

    DP dp;
    vector<int> ar = {1, 3, 7, 5, 10, 3};
    vector<int> val = {6, 1, 7, 7}, wt = {1, 3, 4, 5};
    string text1 = "abc";
    string text2 = "*";
    auto ans =
        dp.maxProfit6(ar, 3);
    cout << ans << " ";
    //  for (auto a : ans)
    //  {
    //      cout << a << " ";
    //  }

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