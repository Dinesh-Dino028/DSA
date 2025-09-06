#include <bits/stdc++.h>
using namespace std;

class Graph
{
private:
public:
    vector<int> bfs(vector<vector<int>> &adj)
    {
        int vis[adj.size()] = {0};
        vis[0] = {1};

        queue<int> q;
        q.push(0);
        vector<int> bfs;
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            bfs.push_back(node);
            for (auto it : adj[node])
            {
                if (!vis[it])
                {
                    vis[it] = {1};
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
        // traverse all its neighbours
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
        int node = 0;
        vector<int> ls;
        dfs(node, adj, vis, ls);
        return ls;
    }

    bool dfsCheck(int node, vector<vector<int>> &adj, vector<int> &vis)
    {
        vis[node] = 2;

        // traverse all adjacent
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
        // Build adjacency list from edge list
        vector<vector<int>> adj(V);
        for (auto &edge : edges)
        {
            if (edge.size() == 2)
                adj[edge[0]].push_back(edge[1]);
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

    bool dfsCheck2(int node, int parent, vector<vector<int>> &adj, vector<int> &vis)
    {
        vis[node] = 1;

        for (auto it : adj[node])
        {
            if (vis[it] == 0)
            {
                if (dfsCheck2(it, node, adj, vis))
                {
                    return true;
                }
            }
            else if (it != parent)
            {
                return true;
            }
        }

        return false;
    }
    bool isCycle2(int V, vector<vector<int>> &edges)
    {
        vector<vector<int>> adj(V);
        for (auto edge : edges)
        {
            if (edge.size() >= 2)
            {
                adj[edge[0]].push_back(edge[1]);
                adj[edge[1]].push_back(edge[0]); // Add reverse direction for undirected graph
            }
        }
        vector<int> vis(V, 0);
        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
            {
                if (dfsCheck2(i, -1, adj, vis))
                {
                    return true;
                }
            }
        }
        return false;
    }
    // Bellman-Ford algorithm to detect negative weight cycle
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

    void tarjansDFS(int u, vector<int> adj[], vector<int> &disc, vector<int> &low, stack<int> &st, vector<bool> &inStack, vector<vector<int>> &ans, int &time)
    {
        disc[u] = low[u] = ++time;
        st.push(u);
        inStack[u] = true;

        for (int v : adj[u])
        {
            if (disc[v] == -1)
            {
                tarjansDFS(v, adj, disc, low, st, inStack, ans, time);
                low[u] = min(low[u], low[v]);
            }
            else if (inStack[v])
            {
                low[u] = min(low[u], disc[v]);
            }
        }

        if (low[u] == disc[u])
        {
            vector<int> scc;
            while (st.top() != u)
            {
                scc.push_back(st.top());
                inStack[st.top()] = false;
                st.pop();
            }
            scc.push_back(u);
            inStack[u] = false;
            st.pop();
            sort(scc.begin(), scc.end());
            ans.push_back(scc);
        }
    }
    vector<vector<int>> tarjans(int V, vector<vector<int>> &edges)
    {
        vector<int> adj[V];
        for (auto &edge : edges)
        {
            if (edge.size() >= 2)
                adj[edge[0]].push_back(edge[1]);
        }
        vector<int> disc(V, -1), low(V, -1);
        vector<bool> inStack(V, false);
        stack<int> st;
        vector<vector<int>> ans;
        int time = 0;
        for (int i = 0; i < V; i++)
        {
            if (disc[i] == -1)
            {
                tarjansDFS(i, adj, disc, low, st, inStack, ans, time);
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }

    void numProvincesdfs(int node, vector<int> adjLi[], int vis[])
    {
        vis[node] = 1;
        for (auto it : adjLi[node])
        {
            if (!vis[it])
            {
                numProvincesdfs(it, adjLi, vis);
            }
        }
    }
    int numProvinces(vector<vector<int>> adj, int V)
    {
        // convert adj matrix to adj list
        vector<int> adjLi[V];

        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (adj[i][j] == 1 && i != j)
                {
                    adjLi[i].push_back(j);
                    adjLi[j].push_back(i);
                }
            }
        }

        int vis[V] = {0};
        int cnt = 0;
        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
            {
                cnt++;
                numProvincesdfs(i, adjLi, vis);
            }
        }
        return cnt;
    }

    void countIslandsbfs(int row, int col, vector<vector<char>> &grid, vector<vector<int>> &vis, int n, int m)
    {
        vis[row][col] = 1;
        queue<pair<int, int>> q;
        q.push({row, col});

        while (!q.empty())
        {
            int crow = q.front().first;
            int ccol = q.front().second;
            q.pop();

            // traverse the 8(neighbour) direction and mark if it L
            for (int delRow = -1; delRow <= 1; delRow++)
            {
                for (int delCol = -1; delCol <= 1; delCol++)
                {
                    int nRow = crow + delRow;
                    int nCol = ccol + delCol;
                    if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && !vis[nRow][nCol] && grid[nRow][nCol] == 'L')
                    {
                        vis[nRow][nCol] = 1;
                        q.push({nRow, nCol});
                    }
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
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < m; col++)
            {
                if (!vis[row][col] && grid[row][col] == 'L')
                {
                    count++;
                    countIslandsbfs(row, col, grid, vis, n, m);
                }
            }
        }
        return count;
    }

    void countDistinctIslandsBfs(int row, int col, vector<vector<int>> &grid, vector<vector<int>> &vis, int n, int m, vector<pair<int, int>> &vec, int row0, int col0)
    {
        vis[row][col] = 1;
        vec.push_back({row - row0, col - col0});

        queue<pair<int, int>> q;
        q.push({row, col});

        // Only 4 directions: up, right, down, left
        int drow[] = {-1, 0, 1, 0};
        int dcol[] = {0, 1, 0, -1};

        while (!q.empty())
        {
            int crow = q.front().first;
            int ccol = q.front().second;
            q.pop();

            for (int i = 0; i < 4; i++)
            {
                int nRow = crow + drow[i];
                int nCol = ccol + dcol[i];

                if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && !vis[nRow][nCol] && grid[nRow][nCol] == 1)
                {
                    vis[nRow][nCol] = 1;
                    vec.push_back({nRow - row0, nCol - col0});
                    q.push({nRow, nCol});
                }
            }
        }
    }
    void countDistinctIslandsDfs(int row, int col, vector<vector<int>> &grid, vector<vector<int>> &vis, int n, int m, vector<pair<int, int>> &vec, int row0, int col0)
    {
        vis[row][col] = 1;
        vec.push_back({row - row0, col - col0});

        // Only 4 directions: up, right, down, left
        int drow[] = {-1, 0, 1, 0};
        int dcol[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++)
        {
            int nRow = row + drow[i];
            int nCol = col + dcol[i];

            if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && !vis[nRow][nCol] && grid[nRow][nCol] == 1)
            {
                vis[nRow][nCol] = 1;
                countDistinctIslandsDfs(nRow, nCol, grid, vis, n, m, vec, row0, col0);
            }
        }
    }
    int countDistinctIslands(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));
        set<vector<pair<int, int>>> st;
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < m; col++)
            {
                if (!vis[row][col] && grid[row][col] == 1)
                {
                    vector<pair<int, int>> vec;
                    countDistinctIslandsBfs(row, col, grid, vis, n, m, vec, row, col);
                    // countDistinctIslandsDfs(row, col, grid, vis, n, m, vec, row, col);
                    st.insert(vec);
                }
            }
        }

        return st.size();
    }

    void closedIslandsDfs(int row, int col, vector<vector<int>> &matrix, vector<vector<int>> &vis, int n, int m)
    {
        vis[row][col] = 1;

        int drow[] = {-1, 0, 1, 0};
        int dcol[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++)
        {
            int nRow = row + drow[i];
            int nCol = col + dcol[i];
            if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m &&
                !vis[nRow][nCol] && matrix[nRow][nCol] == 1)
            {
                closedIslandsDfs(nRow, nCol, matrix, vis, n, m);
            }
        }
    }
    int closedIslands(vector<vector<int>> &matrix, int N, int M)
    {
        vector<vector<int>> vis(N, vector<int>(M, 0));

        // Mark all lands connected to the boundary as visited
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if ((i == 0 || i == N - 1 || j == 0 || j == M - 1) && matrix[i][j] == 1 && !vis[i][j])
                {
                    closedIslandsDfs(i, j, matrix, vis, N, M);
                }
            }
        }

        int count = 0;
        for (int row = 1; row < N - 1; row++)
        {
            for (int col = 1; col < M - 1; col++)
            {
                if (!vis[row][col] && matrix[row][col] == 1)
                {
                    count++;
                    closedIslandsDfs(row, col, matrix, vis, N, M);
                }
            }
        }
        return count;
    }

    bool isBipartiteBfs(int start, int V, vector<int> adj[], int color[])
    {
        queue<int> q;
        q.push(start);
        color[start] = 0;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (int it : adj[node])
            {
                if (color[it] == -1)
                {
                    color[it] = !color[node];
                    q.push(it);
                }
                else if (color[it] == color[node])
                {
                    return false; // Conflict found
                }
            }
        }
        return true;
    }
    bool isBipartite(int V, vector<vector<int>> &edges)
    {
        vector<int> adj[V];

        for (auto &edge : edges)
        {
            if (edge.size() >= 2)
            {
                int u = edge[0], v = edge[1];
                adj[u].push_back(v);
                adj[v].push_back(u); // ✅ Add reverse direction for undirected graph
            }
        }

        int color[V];
        fill(color, color + V, -1); // Initialize all with -1

        for (int i = 0; i < V; i++)
        {
            if (color[i] == -1)
            {
                if (!isBipartiteBfs(i, V, adj, color))
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool isSafe(int node, int color[], vector<int> adj[], int col)
    {
        for (auto it : adj[node])
        {
            if (color[it] == col)
                return false;
        }
        return true;
    }
    bool graphColoringsolve(int node, int color[], int v, vector<int> adj[], int m)
    {
        if (node == v)
            return true;

        for (int col = 1; col <= m; col++)
        {
            if (isSafe(node, color, adj, col))
            {
                color[node] = col;
                if (graphColoringsolve(node + 1, color, v, adj, m))
                    return true;
                color[node] = 0;
            }
        }
        return false;
    }
    bool graphColoring(int v, vector<vector<int>> &edges, int m)
    {
        vector<int> adj[v];

        for (auto &edge : edges)
        {
            if (edge.size() >= 2)
            {
                int u = edge[0];
                int vv = edge[1];
                adj[u].push_back(vv);
                adj[vv].push_back(u);
            }
        }

        int color[v] = {0};
        if (graphColoringsolve(0, color, v, adj, m))
        {
            return true;
        }

        return false;
    }

    vector<int> shortestPath(vector<pair<int, int>> edges, int n, int m, int s, int t)
    {
        // Convert 1-based to 0-based for internal representation
        vector<int> adj[n + 1];
        for (auto edge : edges)
        {
            int u = edge.first;
            int v = edge.second;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> parent(n + 1, -1);
        vector<int> dist(n + 1, 1e9);
        queue<int> q;
        dist[s] = 0;
        q.push(s);

        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            for (auto it : adj[node])
            {
                if (dist[it] > dist[node] + 1)
                {
                    dist[it] = dist[node] + 1;
                    parent[it] = node;
                    q.push(it);
                }
            }
        }

        // Reconstruct path from s to t
        vector<int> path;
        if (dist[t] == 1e9)
            return path; // No path found
        int curr = t;
        while (curr != -1)
        {
            path.push_back(curr);
            curr = parent[curr];
        }
        reverse(path.begin(), path.end());
        return path;
    }

    void topoSort(int node, vector<int> &vis, stack<int> &st, vector<pair<int, int>> adj[])
    {
        vis[node] = 1;
        for (auto it : adj[node])
        {
            int v = it.first;
            if (!vis[v])
            {
                topoSort(v, vis, st, adj);
            }
        }
        st.push(node);
    }
    vector<int> shortestPath(int V, int E, vector<vector<int>> &edges)
    {
        // Convert the edges to adjacency list
        vector<pair<int, int>> adj[V];
        for (auto edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            adj[u].push_back({v, w});
        }

        vector<int> vis(V, 0);
        stack<int> st;
        // Topological sort
        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
            {
                topoSort(i, vis, st, adj);
            }
        }

        // Shortest path
        vector<int> dis(V, 1e9);
        dis[0] = 0; // Source is 0
        while (!st.empty())
        {
            int node = st.top();
            st.pop();
            if (dis[node] != 1e9)
            {
                for (auto it : adj[node])
                {
                    int v = it.first;
                    int w = it.second;

                    if (dis[node] + w < dis[v])
                    {
                        dis[v] = dis[node] + w;
                    }
                }
            }
        }
        // Set unreachable nodes to -1
        for (int i = 0; i < V; i++)
        {
            if (dis[i] == 1e9)
                dis[i] = -1;
        }
        return dis;
    }

    vector<int> dijkstra(int V, vector<vector<int>> &edges, int src)
    {
        // Code here
        vector<pair<int, int>> adj[V];
        for (auto &edge : edges)
        {
            int u = edge[0], v = edge[1], w = edge[2];
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
                int edgeWeight = it.second;

                if (dis + edgeWeight < dist[adjNode])
                {
                    dist[adjNode] = dis + edgeWeight;
                    pq.push({dist[adjNode], adjNode});
                }
            }
        }
        return dist;
    }

    vector<int> dijkstraUsingSet(int V, vector<vector<int>> &edges, int src)
    {
        // Code here
        // create adj list
        vector<pair<int, int>> adj[V];
        for (auto edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        // use set
        vector<int> dist(V, 1e9);

        set<pair<int, int>> st;
        st.insert({0, src});
        dist[src] = 0;

        while (!st.empty())
        {
            auto it = *(st.begin());

            int node = it.second;
            int dis = it.first;
            st.erase(it);

            for (auto it : adj[node])
            {
                int adjNode = it.first;
                int edgeW = it.second;

                if (dis + edgeW < dist[adjNode])
                {
                    if (dist[adjNode] != 1e9)
                    {
                        st.erase({dist[adjNode], adjNode});
                    }
                    dist[adjNode] = dis + edgeW;
                    st.insert({dist[adjNode], adjNode});
                }
            }
        }
        return dist;
    }

    int minStepToReachTarget(vector<int> &knightPos, vector<int> &targetPos, int n)
    {
        // Code here
        vector<vector<bool>> visited(n + 1, vector<bool>(n + 1, false));

        int dx[] = {2, 2, -2, -2, 1, -1, 1, -1};
        int dy[] = {1, -1, 1, -1, 2, 2, -2, -2};

        queue<pair<pair<int, int>, int>> q;
        q.push({{knightPos[0], knightPos[1]}, 0});

        while (!q.empty())
        {
            auto [position, steps] = q.front();
            q.pop();

            int x = position.first;
            int y = position.second;

            if (x == targetPos[0] && y == targetPos[1])
            {
                return steps;
            }

            for (int i = 0; i < 8; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];

                // Check if the new position is within bounds and not visited
                if (nx >= 1 && nx <= n && ny >= 1 && ny <= n && !visited[nx][ny])
                {
                    visited[nx][ny] = true;
                    q.push({{nx, ny}, steps + 1});
                }
            }
        }
        return -1;
    }

    int shortestDistance(int N, int M, vector<vector<int>> A, int X, int Y)
    {
        if (A[0][0] == 0 || A[X][Y] == 0)
            return -1;

        vector<vector<int>> vis(N, vector<int>(M, 0));
        queue<pair<pair<int, int>, int>> q;
        q.push({{0, 0}, 0});
        vis[0][0] = 1;

        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        while (!q.empty())
        {
            auto curr = q.front();
            q.pop();
            int x = curr.first.first;
            int y = curr.first.second;
            int steps = curr.second;

            if (x == X && y == Y)
                return steps;

            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= 0 && nx < N && ny >= 0 && ny < M && !vis[nx][ny] && A[nx][ny] == 1)
                {
                    vis[nx][ny] = 1;
                    q.push({{nx, ny}, steps + 1});
                }
            }
        }
        return -1;
    }

    bool is_PossibleDfs(int x, int y, vector<vector<bool>> &vis, vector<vector<int>> &grid, int n)
    {
        if (x < 0 || x >= n || y < 0 || y >= n || vis[x][y] || grid[x][y] == 0)
        {
            return false;
        }
        if (grid[x][y] == 2)
        {
            return true;
        }
        vis[x][y] = true;
        return is_PossibleDfs(x + 1, y, vis, grid, n) ||
               is_PossibleDfs(x - 1, y, vis, grid, n) ||
               is_PossibleDfs(x, y + 1, vis, grid, n) ||
               is_PossibleDfs(x, y - 1, vis, grid, n);
    }
    bool is_Possible(vector<vector<int>> &grid)
    {
        // code here
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<bool>> vis(n, vector<bool>(m, false));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == 1)
                {
                    return is_PossibleDfs(i, j, vis, grid, n);
                }
            }
        }
        return false;
    }

    int helpaterp(vector<vector<int>> hospital)
    {
        // code here
        int n = hospital.size();
        int m = hospital[0].size();
        vector<vector<bool>> vis(n, vector<bool>(m, false));

        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        queue<pair<pair<int, int>, int>> q;

        int countUninfected = 0;
        int time = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (hospital[i][j] == 2)
                {
                    q.push({{i, j}, 0});
                    vis[i][j] = true;
                }
                else if (hospital[i][j] == 1)
                {
                    countUninfected++;
                }
            }
        }

        int infected = 0;

        while (!q.empty())
        {
            int x = q.front().first.first;
            int y = q.front().first.second;

            int t = q.front().second;

            q.pop();

            time = max(time, t);

            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx >= 0 && nx < n && ny >= 0 && ny < n && !vis[nx][ny] && hospital[nx][ny] == 1)
                {
                    vis[nx][ny] = true;
                    q.push({{nx, ny}, t + 1});
                    infected++;
                }
            }
        }

        return (infected == countUninfected) ? time : -1;
    }

    int minimumCostPath(vector<vector<int>> &grid)
    {
        // implement dijkrstra algo
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> dis(n, vector<int>(m, INT_MAX));
        // Min-heap: {cost, {x, y}}
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
        pq.push({grid[0][0], {0, 0}});
        dis[0][0] = grid[0][0];

        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        while (!pq.empty())
        {
            auto cur = pq.top();
            pq.pop();
            int cost = cur.first;

            int x = cur.second.first;
            int y = cur.second.second;
            if (x == n - 1 && y == m - 1)
            {
                return cost;
            }
            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx >= 0 && nx < n && ny >= 0 && ny < n)
                {
                    if (cost + grid[nx][ny] < dis[nx][ny])
                    {
                        dis[nx][ny] = cost + grid[nx][ny];
                        pq.push({dis[nx][ny], {nx, ny}});
                    }
                }
            }
        }
        return -1;
    }

    int wordLadderLength(string startWord, string targetWord, vector<string> &wordList)
    {
        queue<pair<string, int>> q;
        q.push({startWord, 1});

        set<string> st;
        st.insert(wordList.begin(), wordList.end());
        st.erase(startWord);
        while (!q.empty())
        {
            string word = q.front().first;
            int steps = q.front().second;
            q.pop();
            if (word == targetWord)
            {
                return steps;
            }
            for (int i = 0; i < word.size(); i++)
            {
                char originalWord = word[i];
                for (char c = 'a'; c <= 'z'; c++)
                {
                    word[i] = c;
                    if (st.find(word) != st.end())
                    {
                        st.erase(word);
                        q.push({word, steps + 1});
                    }
                }
                word[i] = originalWord;
            }
        }
        return 0;
    }

    vector<vector<string>> findSequences(string beginWord, string endWord, vector<string> &wordList)
    {
        // code here
        queue<vector<string>> q;
        q.push({beginWord});

        vector<vector<string>> ans;

        vector<string> usedOnLevel;
        usedOnLevel.push_back(beginWord);
        unordered_set<string> st;
        st.insert(wordList.begin(), wordList.end());
        st.erase(beginWord);

        int level = 0;

        while (!q.empty())
        {
            vector<string> vec = q.front();
            q.pop();

            // erase all levels that used on the previous level

            if (vec.size() > level)
            {
                level++;
                for (auto it : usedOnLevel)
                {
                    st.erase(it);
                }
                usedOnLevel.clear();
            }

            string word = vec.back();

            if (word == endWord)
            {
                if (ans.size() == 0)
                {
                    ans.push_back(vec);
                }
                else if (ans[0].size() > 0)
                {
                    ans.push_back(vec);
                }
            }

            for (int i = 0; i < word.size(); i++)
            {
                char originalWord = word[i];
                for (char c = 'a'; c <= 'z'; c++)
                {
                    word[i] = c;
                    if (st.count(word) > 0)
                    {
                        vec.push_back(word);
                        q.push(vec);

                        // mark on visited on level
                        usedOnLevel.push_back(word);
                        vec.pop_back();
                    }
                }
                word[i] = originalWord;
            }
        }
        return ans;
    }

    void floydWarshall(vector<vector<int>> &dist)
    {
        // Code here
        int n = dist.size();
        for (int k = 0; k < n; k++)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (dist[i][k] < 1e8 && dist[k][j] < 1e8)
                    {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
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

    void floodFillDfs(int row, int col, vector<vector<int>> &image, int iniColor, int newColor, vector<vector<int>> &ans, int delRow[], int delCol[])
    {
        ans[row][col] = newColor;

        int n = image.size();
        int m = image[0].size();

        for (int i = 0; i < 4; i++)
        {
            int nRow = row + delRow[i];
            int nCol = col + delCol[i];
            if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && image[nRow][nCol] == iniColor && ans[nRow][nCol] != newColor)
            {
                floodFillDfs(nRow, nCol, image, iniColor, newColor, ans, delRow, delCol);
            }
        }
    }
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor)
    {
        // Code here
        vector<vector<int>> ans = image;
        int iniColor = image[sr][sc];
        // using dfs path
        int dx[] = {-1, 0, +1, 0};
        int dy[] = {0, +1, 0, -1};
        floodFillDfs(sr, sc, image, iniColor, newColor, ans, dx, dy);
        return ans;
    }

    void fill2dfs(int row, int col, vector<vector<char>> &mat, int n, int m)
    {
        // Mark this cell as visited with '#'
        mat[row][col] = '#';

        int drow[] = {-1, 1, 0, 0};
        int dcol[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++)
        {
            int newRow = row + drow[i];
            int newCol = col + dcol[i];

            if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m && mat[newRow][newCol] == 'O')
            {
                fill2dfs(newRow, newCol, mat, n, m);
            }
        }
    }
    vector<vector<char>> fill2(vector<vector<char>> &mat)
    {
        int n = mat.size();
        int m = mat[0].size();

        // Step 1: Run DFS from all border 'O's
        for (int i = 0; i < n; i++)
        {
            if (mat[i][0] == 'O')
                fill2dfs(i, 0, mat, n, m);
            if (mat[i][m - 1] == 'O')
                fill2dfs(i, m - 1, mat, n, m);
        }
        for (int j = 0; j < m; j++)
        {
            if (mat[0][j] == 'O')
                fill2dfs(0, j, mat, n, m);
            if (mat[n - 1][j] == 'O')
                fill2dfs(n - 1, j, mat, n, m);
        }

        // Step 2: Change all remaining 'O' to 'X'
        // Step 3: Restore '#' back to 'O'
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (mat[i][j] == 'O')
                    mat[i][j] = 'X';
                else if (mat[i][j] == '#')
                    mat[i][j] = 'O';
            }
        }

        return mat;
    }

    void findMaxAreaDfs(int row, int col, vector<vector<int>> &grid, int &area, vector<vector<int>> &vis, int n, int m)
    {
        area++;
        vis[row][col] = 1;
        // 8 directions: up, down, left, right, and 4 diagonals
        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        for (int i = 0; i < 8; i++)
        {
            int nRow = row + dx[i];
            int nCol = col + dy[i];

            if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && grid[nRow][nCol] == 1 && vis[nRow][nCol] == 0)
            {
                findMaxAreaDfs(nRow, nCol, grid, area, vis, n, m);
            }
        }
    }
    int findMaxArea(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));
        int maxArea = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == 1 && vis[i][j] == 0)
                {
                    int area = 0;
                    findMaxAreaDfs(i, j, grid, area, vis, n, m);
                    maxArea = max(maxArea, area);
                }
            }
        }
        return maxArea;
    }

    int orangesRotting(vector<vector<int>> &mat)
    {
        // Code here
        int n = mat.size();
        int m = mat[0].size();

        vector<vector<int>> vis(n, vector<int>(m, 0));
        queue<pair<pair<int, int>, int>> q;
        int tm = 0;

        // Step 1: Enqueue all initially rotten oranges
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (mat[i][j] == 2)
                {
                    q.push({{i, j}, 0});
                    vis[i][j] = 2;
                }
            }
        }

        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        // Step 2: BFS traversal to rot adjacent oranges
        while (!q.empty())
        {
            int r = q.front().first.first;
            int c = q.front().first.second;
            int t = q.front().second;
            q.pop();
            tm = max(tm, t);

            for (int i = 0; i < 4; i++)
            {
                int nRow = r + dx[i];
                int nCol = c + dy[i];

                if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && vis[nRow][nCol] == 0 && mat[nRow][nCol] == 1)
                {
                    q.push({{nRow, nCol}, t + 1});
                    vis[nRow][nCol] = 2;
                }
            }
        }

        // Step 3: Check for any remaining fresh oranges
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (mat[i][j] == 1 && vis[i][j] != 2)
                {
                    return -1;
                }
            }
        }

        return tm;
    }

    void topoSortDfs(int node, int vis[], vector<int> adj[], stack<int> &st)
    {
        vis[node] = 1;

        for (auto it : adj[node])
        {
            if (!vis[it])
            {
                topoSortDfs(it, vis, adj, st);
            }
        }
        st.push(node);
    }
    vector<int> topoSort(int V, vector<vector<int>> &edges)
    {
        // code here
        // create adj list
        vector<int> adj[V];
        for (auto edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
        }
        int vis[V] = {0};
        stack<int> st;
        vector<int> ans;
        // use dfs
        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
            {
                topoSortDfs(i, vis, adj, st);
            }
        }

        while (!st.empty())
        {
            ans.push_back(st.top());
            st.pop();
        }

        return ans;
    }

    // Helper DFS to detect cycle in directed graph
    bool isPossibleDfs(int node, vector<int> adj[], vector<int> &vis, vector<int> &recStack)
    {
        vis[node] = 1;
        recStack[node] = 1;

        for (auto it : adj[node])
        {
            if (!vis[it])
            {
                if (isPossibleDfs(it, adj, vis, recStack))
                    return true;
            }
            else if (recStack[it])
            {
                return true; // Cycle detected
            }
        }
        recStack[node] = 0;
        return false;
    }
    bool isPossible(int N, int P, vector<pair<int, int>> &prerequisites)
    {
        // Build adjacency list for directed graph
        vector<int> adj[N];
        for (auto &p : prerequisites)
        {
            int u = p.second; // To do u, you must do v first
            int v = p.first;
            adj[u].push_back(v);
        }

        vector<int> vis(N, 0), recStack(N, 0);

        for (int i = 0; i < N; i++)
        {
            if (!vis[i])
            {
                if (isPossibleDfs(i, adj, vis, recStack))
                    return false; // Cycle found, not possible
            }
        }
        return true; // No cycle, possible to finish all tasks
    }

    void findOrderDfs(int node, int vis[], queue<int> &q, vector<int> adj[])
    {
        vis[node] = 1;

        for (auto it : adj[node])
        {
            if (!vis[it])
            {
                findOrderDfs(it, vis, q, adj);
            }
        }
        q.push(node);
    }
    vector<int> findOrder(int n, vector<vector<int>> prerequisites)
    {
        // code here
        // create adj list
        vector<int> adj[n];

        for (auto p : prerequisites)
        {
            int u = p[0];
            int v = p[1];
            adj[u].push_back(v);
        }

        queue<int> q;
        int vis[n] = {0};

        for (int i = 0; i < n; i++)
        {
            if (!vis[i])
            {
                findOrderDfs(i, vis, q, adj);
            }
        }
        vector<int> ans;
        while (!q.empty())
        {
            ans.push_back(q.front());
            q.pop();
        }
        return ans;
    }

    vector<int> findOrder2(int numCourses, vector<vector<int>> &prerequisites)
    {
        // Kahn's algorithm (BFS topological sort)
        vector<int> adj[numCourses];
        vector<int> indegree(numCourses, 0);
        for (auto &p : prerequisites)
        {
            int u = p[1];
            int v = p[0];
            adj[u].push_back(v);
            indegree[v]++;
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++)
        {
            if (indegree[i] == 0)
                q.push(i);
        }

        vector<int> ans;
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            ans.push_back(node);
            for (auto it : adj[node])
            {
                indegree[it]--;
                if (indegree[it] == 0)
                    q.push(it);
            }
        }
        if (ans.size() != numCourses)
            return {}; // Cycle detected, not possible
        return ans;
    }

    vector<int> eventualSafeNodes(int V, vector<int> adj[])
    {
        // code here
        // reverse adj
        vector<int> adjRev[V];
        int indegree[V] = {0};
        for (int i = 0; i < V; i++)
        {
            for (auto it : adj[i])
            {
                adjRev[it].push_back(i);
                indegree[i]++;
            }
        }

        // add indegree 0 to queue
        queue<int> q;
        for (int i = 0; i < V; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }
        vector<int> safeNodes;
        // remove all indegree which has only 1 and add to queue
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            safeNodes.push_back(node);
            for (auto it : adjRev[node])
            {
                indegree[it]--;
                if (indegree[it] == 0)
                {
                    q.push(it);
                }
            }
        }

        sort(safeNodes.begin(), safeNodes.end());

        return safeNodes;
    }

    vector<int> topoSortKhans(int V, vector<int> adj[])
    {
        vector<int> adjRev[V];
        int indegrees[V] = {0};
        for (int i = 0; i < V; i++)
        {
            for (auto it : adj[i])
            {
                adjRev[it].push_back(i);
                indegrees[it]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < V; i++)
        {
            if (indegrees[i] == 0)
            {
                q.push(i);
            }
        }
        vector<int> topo;
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            topo.push_back(node);
            for (auto it : adjRev[node])
            {
                indegrees[it]--;
                if (indegrees[it] == 0)
                {
                    q.push(it);
                }
            }
        }
        return topo;
    }
    string findOrder(vector<string> &words)
    {
        vector<int> adj[26];
        vector<int> indegree(26, 0);
        vector<bool> present(26, false);

        // Mark present letters
        for (string &word : words)
        {
            for (char c : word)
            {
                present[c - 'a'] = true;
            }
        }

        // Build graph from adjacent words
        for (int i = 0; i < words.size() - 1; i++)
        {
            string &s1 = words[i];
            string &s2 = words[i + 1];
            int len = min(s1.size(), s2.size());

            bool foundDiff = false;
            for (int j = 0; j < len; j++)
            {
                if (s1[j] != s2[j])
                {
                    adj[s1[j] - 'a'].push_back(s2[j] - 'a');
                    indegree[s2[j] - 'a']++;
                    foundDiff = true;
                    break;
                }
            }

            if (!foundDiff && s1.size() > s2.size())
            {
                return ""; // Invalid case: s1 longer but no diff → invalid order
            }
        }

        // Kahn's algorithm
        queue<int> q;
        for (int i = 0; i < 26; i++)
        {
            if (present[i] && indegree[i] == 0)
            {
                q.push(i);
            }
        }

        string ans;
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            ans += char(node + 'a');
            for (int neighbor : adj[node])
            {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0)
                {
                    q.push(neighbor);
                }
            }
        }

        // Check for cycle
        int totalChars = count(present.begin(), present.end(), true);
        if (ans.size() != totalChars)
            return "";

        return ans;
    }

    int spanningTree(int V, vector<vector<int>> adj[])
    {
        // code here
        vector<int> vis(V, 0);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // w, node
        pq.push({0, 0});
        int sum = 0;
        while (!pq.empty())
        {
            auto it = pq.top();
            pq.pop();
            int node = it.second;
            int w = it.first;

            if (vis[node] == 1)
            {
                continue;
            }
            vis[node] = 1;

            sum += w;

            for (auto it : adj[node])
            {
                int adjNode = it[0];
                int edW = it[1];
                if (!vis[adjNode])
                {
                    pq.push({edW, adjNode});
                }
            }
        }
        return sum;
    }
};

int main()
{
    Graph g;

    vector<int> n2 = {9, 4, 9, 9};
    vector<int> n1 = {6, 7, 6, 4};
    vector<int> n3 = {8, 3, 3, 7};
    vector<int> n4 = {7, 4, 9, 10};
    vector<int> n5 = {1, 0, 1, 0, 0, 1, 1};
    vector<int> n6 = {1, 1, 1, 1, 0, 0, 1};
    vector<int> n7 = {0, 0, 0, 0, 0, 0, 0};
    vector<int> n8 = {0, 0, 1, 0, 1, 0, 0};

    vector<vector<int>> input;
    input.push_back(n1);
    input.push_back(n2);
    input.push_back(n3);
    input.push_back(n4);
    //   input.push_back(n5);
    //   input.push_back(n6);
    //   input.push_back(n7);
    //   input.push_back(n8);

    // Example test input for numProvinces (adjacency matrix for 3 nodes)
    // 1---3
    // |   |
    // 2---/
    // vector<vector<int>> input = {
    //     {1, 0, 1},
    //     {0, 1, 0},
    //     {1, 0, 1}};

    // Example input for isBipartite: 4 nodes, edges between 0-1, 1-2, 2-3, 3-0 (even cycle, bipartite)
    int V = 4;
    vector<vector<int>> edges = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 0}};

    string startWord = "der";
    string targetWord = "dfs";

    vector<string> wordList = {"des", "der", "dfr", "dgt", "dfs"};

    vector<vector<int>> input2 = {{1, 1, 0, 0, 0},
                                  {1, 1, 0, 0, 0},
                                  {0, 0, 0, 1, 1},
                                  {0, 0, 0, 1, 1}};

    vector<pair<int, int>> prerequisites = {{1, 0}, {0, 1}};

    int grid[5][5] = {{1, 1, 0, 0, 0},
                      {1, 1, 0, 0, 0},
                      {0, 0, 0, 1, 1},
                      {0, 0, 0, 1, 1}};

    // Example input for findOrder2 (Kahn's algorithm for course schedule)
    int numCourses = 6;
    vector<vector<int>> prerequisites2 = {
        {5, 0},
        {4, 0},
        {5, 2},
        {2, 3},
        {3, 1},
        {4, 1}};
    auto ans = g.findOrder2(numCourses, prerequisites2);
    //    cout << ans;

    for (auto a : ans)
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
