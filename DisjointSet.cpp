#include <bits/stdc++.h>
using namespace std;

class DisjointSet
{
private:
public:
    vector<int> size;
    vector<int> rank;
    vector<int> parent;

    DisjointSet(int n)
    {
        size.resize(n + 1);
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++)
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
        return parent[node] = findUPar(parent[node]); // path compression
    }

    void unionByRank(int u, int v)
    {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v)
        {
            return;
        }
        if (rank[ulp_u] < rank[ulp_v])
        {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u])
        {
            parent[ulp_v] = ulp_u;
        }
        else
        {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v)
    {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v)
        {
            return;
        }
        if (size[ulp_u] < size[ulp_v])
        {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else
        {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class DisjointSetPractice
{
public:
    int makeConnected(int n, vector<vector<int>> &connections)
    {
        DisjointSet ds(n);
        int extraCon = 0;
        // check if extra edges
        for (auto connection : connections)
        {
            int u = connection[0];
            int v = connection[1];
            if (ds.findUPar(u) == ds.findUPar(v))
            {
                extraCon++;
            }
            else
            {
                ds.unionBySize(u, v);
            }
        }

        // check connected components and detect sufficient edge is there(n-1)
        int conComponent = 0;
        for (int i = 0; i < n; i++)
        {
            if (ds.parent[i] == i)
            {
                conComponent++;
            }
        }
        int ans = conComponent - 1;
        if (extraCon >= ans)
        {
            return ans;
        }
        return -1;
    }

    int minSwaps(vector<int> &arr)
    {
        // Code here
        vector<pair<int, int>> v;
        int swaps = 0;
        for (int i = 0; i < arr.size(); i++)
        {
            v.push_back({arr[i], i});
        }
        sort(v.begin(), v.end());

        for (int i = 0; i < arr.size(); i++)
        {
            auto it = v[i];
            int val = it.first;
            int index = it.second;
            if (i != index)
            {
                swaps++;
                swap(v[i], v[index]);
                i--;
            }
        }
        return swaps;
    }

    // Helper function to get the kth prime number (1-based, 1 is considered composite)
    int getKthPrime(int k)
    {
        // Precompute a list of primes up to a reasonable limit
        // 1 is considered composite, so we start from 2
        static vector<int> primes;
        static bool computed = false;
        if (!computed)
        {
            int limit = 100000; // Should be enough for reasonable k
            vector<bool> isPrime(limit + 1, true);
            isPrime[0] = isPrime[1] = false;
            for (int i = 2; i * i <= limit; ++i)
            {
                if (isPrime[i])
                {
                    for (int j = i * i; j <= limit; j += i)
                    {
                        isPrime[j] = false;
                    }
                }
            }
            for (int i = 2; i <= limit; ++i)
            {
                if (isPrime[i])
                    primes.push_back(i);
            }
            computed = true;
        }
        if (k <= 0 || k > (int)primes.size())
            return -1;
        return primes[k - 1];
    }
    int helpSanta(int n, int m, vector<vector<int>> &g)
    {
        if (m == 0)
            return -1; // No connections

        DisjointSet ds(n);
        for (auto &it : g)
        {
            int u = it[0] - 1; // 0-based indexing
            int v = it[1] - 1;
            ds.unionBySize(u, v);
        }

        vector<int> groupSize(n, 0);
        int maxGroup = 0;
        for (int i = 0; i < n; i++)
        {
            int root = ds.findUPar(i);
            groupSize[root]++;
        }
        for (int i = 0; i < n; i++)
        {
            maxGroup = max(maxGroup, groupSize[i]);
        }
        if (maxGroup <= 1)
            return -1; // No group with more than one girl

        return getKthPrime(maxGroup);
    }

    long long int numberOfPairs(vector<vector<int>> &pairs, int p, int n)
    {
        // n = total students, p = number of pairs, pairs = same branch pairs
        DisjointSet ds(n);
        for (auto &pr : pairs)
        {
            ds.unionBySize(pr[0], pr[1]);
        }
        // Count size of each branch (connected component)
        vector<long long> branchSizes;
        for (int i = 0; i < n; ++i)
        {
            if (ds.findUPar(i) == i)
            {
                branchSizes.push_back(ds.size[i]);
            }
        }
        // Total pairs = sum of (size[i] * sum of sizes after i)
        long long ans = 0, suffixSum = 0;
        for (int i = (int)branchSizes.size() - 1; i >= 0; --i)
        {
            ans += branchSizes[i] * suffixSum;
            suffixSum += branchSizes[i];
        }
        return ans;
    }

    bool isValid(int row, int col, int n)
    {
        if (row >= 0 && row < n && col >= 0 && col < n)
        {
            return true;
        }
        return false;
    }
    int largestIsland(vector<vector<int>> &grid)
    {
        int n = grid.size();
        DisjointSet ds(n);
        int mx = 0;
        // step-1 convert the unionbysize of all connected componenets
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < n; col++)
            {
                if (grid[row][col] == 0)
                {
                    continue;
                }
                int dx[] = {-1, 0, 1, 0};
                int dy[] = {0, 1, 0, -1};

                for (int i = 0; i < 4; i++)
                {
                    int nRow = row + dx[i];
                    int nCol = col + dy[i];
                    if (isValid(nRow, nCol, n) && grid[nRow][nCol] == 1)
                    {
                        int nodeNo = row * n + col;
                        int adjNodeNo = nRow * n + nCol;

                        ds.unionBySize(nodeNo, adjNodeNo);
                    }
                }
            }
        }

        // step-2 try 0 for node to get the max size
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < n; col++)
            {
                if (grid[row][col] == 1)
                {
                    continue;
                }
                int dx[] = {-1, 0, 1, 0};
                int dy[] = {0, 1, 0, -1};
                set<int> componenets;

                for (int i = 0; i < 4; i++)
                {
                    int nRow = row + dx[i];
                    int nCol = col + dy[i];
                    if (isValid(nRow, nCol, n))
                    {
                        if (grid[nRow][nCol] == 1)
                        {
                            componenets.insert(ds.findUPar(nRow * row + nCol));
                        }
                    }
                }

                // find the size
                int sizeOfTotal = 0;
                for (auto it : componenets)
                {
                    sizeOfTotal += ds.size[it];
                }
                mx = max(mx, sizeOfTotal + 1);
            }
        }
        for (int cellNo = 0; cellNo < n * n; cellNo++)
        {
            mx = max(mx, ds.size[ds.findUPar(cellNo)]);
        }
        return mx;
    }

    bool dfs(int node, int parent, int c, int d, vector<int> adj[], vector<bool> &visited, vector<int> &tin, vector<int> &low, int &time, bool &foundBridge)
    {

        visited[node] = true;
        tin[node] = low[node] = time++;

        for (int it : adj[node])
        {
            if (!visited[it])
            {
                dfs(it, node, c, d, adj, visited, tin, low, time, foundBridge);
                low[node] = min(low[node], low[it]);

                // Check for bridge
                if (low[it] > tin[node])
                {
                    if ((node == c && it == d) || (node == d && it == c))
                    {
                        foundBridge = true;
                    }
                }
            }
            else if (it != parent)
            {
                low[node] = min(low[node], tin[it]);
            }
        }
        return foundBridge;
    }
    bool isBridge(int V, vector<vector<int>> &edges, int c, int d)
    {
        vector<int> adj[V];
        for (auto &e : edges)
        {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<bool> visited(V, false);
        vector<int> tin(V, -1), low(V, -1);
        int time = 0;
        bool foundBridge = false;

        // DFS for all components
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                dfs(i, -1, c, d, adj, visited, tin, low, time, foundBridge);
            }
        }

        return foundBridge;
    }

    void articulationPointsDfs(int node, int parent, vector<int> adj[], int V, int tin[], int low[], int &timer, vector<int> &visited, vector<int> &mark)
    {
        visited[node] = 1;
        tin[node] = low[node] = timer++;
        int child = 0;
        for (auto it : adj[node])
        {
            if (it == parent)
                continue;
            if (!visited[it])
            {
                articulationPointsDfs(it, node, adj, V, tin, low, timer, visited, mark);
                low[node] = min(low[node], low[it]);
                if (low[it] >= tin[node] && parent != -1)
                {
                    mark[node] = 1;
                }
                child++;
            }
            else
            {
                low[node] = min(low[node], tin[it]);
            }
        }
        if (child > 1 && parent == -1)
        {
            mark[node] = 1;
        }
    }
    vector<int> articulationPoints(int V, vector<int> adj[])
    {
        // Code here
        vector<int> visited(V, 0);
        int tin[V];
        int low[V];
        int timer = 0;
        vector<int> mark(V, 0);

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                articulationPointsDfs(i, -1, adj, V, tin, low, timer, visited, mark);
            }
        }
        vector<int> ans;
        for (int i = 0; i < V; i++)
        {
            if (mark[i] == 1)
            {
                ans.push_back(i);
            }
        }
        if (ans.size() == 0)
        {
            return {-1};
        }
        sort(ans.begin(), ans.end());
        return ans;
    }

    void criticalConnectionsDfs(int node, int parent, vector<int> adj[], int V, int tin[], int low[], int &timer, vector<int> &visited, vector<vector<int>> &bridges)
    {
        visited[node] = 1;
        tin[node] = low[node] = timer++;
        for (auto it : adj[node])
        {
            if (it == parent)
                continue;
            if (!visited[it])
            {
                criticalConnectionsDfs(it, node, adj, V, tin, low, timer, visited, bridges);
                low[node] = min(low[node], low[it]);
                if (low[it] > tin[node])
                {
                    bridges.push_back({min(node, it), max(node, it)});
                }
            }
            else
            {
                low[node] = min(low[node], tin[it]);
            }
        }
    }
    vector<vector<int>> criticalConnections(int v, vector<vector<int>> &edges)
    {
        vector<int> adj[v];
        for (auto &edge : edges)
        {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        vector<int> visited(v, 0);
        int tin[v];
        int low[v];
        int timer = 0;
        vector<vector<int>> bridges;

        for (int i = 0; i < v; i++)
        {
            if (!visited[i])
            {
                criticalConnectionsDfs(i, -1, adj, v, tin, low, timer, visited, bridges);
            }
        }
        sort(bridges.begin(), bridges.end());
        return bridges;
    }

    void kosarajuDfs(int node, vector<vector<int>> &adj, vector<int> &vis, stack<int> &st)
    {
        vis[node] = 1;

        for (auto it : adj[node])
        {
            if (!vis[it])
            {
                kosarajuDfs(it, adj, vis, st);
            }
        }
        st.push(node);
    }
    void kosarajuDfs2(int node, vector<vector<int>> &adj, vector<int> &vis)
    {
        vis[node] = 1;

        for (auto it : adj[node])
        {
            if (!vis[it])
            {
                kosarajuDfs2(it, adj, vis);
            }
        }
    }
    int kosaraju(vector<vector<int>> &adj)
    {
        // code here
        int n = adj.size();
        vector<int> vis(n, 0);
        stack<int> st;

        // First DFS to fill stack according to finish times
        for (int i = 0; i < n; i++)
        {
            if (!vis[i])
            {
                kosarajuDfs(i, adj, vis, st);
            }
        }

        // Reverse the graph
        vector<vector<int>> revAdj(n);
        for (int i = 0; i < n; i++)
        {
            for (auto it : adj[i])
            {
                revAdj[it].push_back(i);
            }
        }

        // Second DFS on reversed graph
        fill(vis.begin(), vis.end(), 0);
        int scc = 0;
        while (!st.empty())
        {
            int node = st.top();
            st.pop();
            if (!vis[node])
            {
                scc++;
                kosarajuDfs2(node, revAdj, vis);
            }
        }
        return scc;
    }

    bool openGatesDfs(int index, int i, int j, string name, vector<vector<char>> &map, vector<vector<bool>> &vis, int dx[], int dy[])
    {
        int r = map.size();
        int c = map[0].size();

        // Check boundaries and visited
        if (i < 0 || i >= r || j < 0 || j >= c || vis[i][j] || map[i][j] != name[index])
        {
            return false;
        }
        // If last character matches
        if (index == name.size() - 1)
        {
            return true;
        }

        vis[i][j] = true;

        for (int dir = 0; dir < 8; dir++)
        {
            int nRow = i + dx[dir];
            int nCol = j + dy[dir];

            if (openGatesDfs(index + 1, nRow, nCol, name, map, vis, dx, dy))
            {
                vis[i][j] = false;
                return true;
            }
        }
        vis[i][j] = false;
        return false;
    }
    bool nameExists(string name, vector<vector<char>> &map)
    {
        int r = map.size();
        int c = map[0].size();

        // Directions: 8-connected neighbors
        int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
        int dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (map[i][j] == name[0])
                {
                    vector<vector<bool>> vis(r, vector<bool>(c, false));
                    if (openGatesDfs(0, i, j, name, map, vis, dx, dy))
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    vector<string> openGates(vector<vector<char>> &map, vector<string> &gate_names)
    {
        // Code here
        unordered_set<string> uniqueGates(gate_names.begin(), gate_names.end());
        vector<string> ans;

        for (auto gate : uniqueGates)
        {
            if (nameExists(gate, map))
            {
                ans.push_back(gate);
            }
        }

        return ans;
    }
};

int main()
{
    // disjointSet ds(7);
    // ds.unionBySize(1, 2);
    // ds.unionBySize(2, 3);
    // ds.unionBySize(4, 5);
    // ds.unionBySize(6, 7);
    // ds.unionBySize(5, 6);

    // cout << "BEFORE\n";
    // if (ds.findUPar(3) == ds.findUPar(7))
    // {
    //     cout << "Same\n";
    // }
    // else
    // {
    //     cout << "Not Same\n";
    // }
    // ds.unionBySize(3, 7);

    // cout << "AFTER\n";
    // if (ds.findUPar(3) == ds.findUPar(7))
    // {
    //     cout << "Same\n";
    // }
    // else
    // {
    //     cout << "Not Same\n";
    // }

    DisjointSetPractice dsp;
    vector<vector<int>> input = {{1, 0}, {0, 1}};
    vector<int> arr = {2, 8, 5, 4};
    cout << dsp.minSwaps(arr);

    return 0;
}