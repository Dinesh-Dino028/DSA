#include <bits/stdc++.h>
#include <algorithm>
#include <cmath>
using namespace std;

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;

    Node(int x)
    {
        data = x;
        left = right = NULL;
    }
};

class Tree
{
private:
public:
    vector<int> preorder(Node *root)
    {
        vector<int> ans;
        if (!root)
        {
            return ans;
        }
        ans.push_back(root->data);
        vector<int> left = preorder(root->left);
        vector<int> right = preorder(root->right);
        ans.insert(ans.end(), left.begin(), left.end());
        ans.insert(ans.end(), right.begin(), right.end());
        return ans;
    }

    vector<int> inOrder(Node *root)
    {
        vector<int> ans;
        if (!root)
        {
            return ans;
        }
        vector<int> left = inOrder(root->left);
        vector<int> right = inOrder(root->right);
        ans.insert(ans.end(), left.begin(), left.end());
        ans.push_back(root->data);
        ans.insert(ans.end(), right.begin(), right.end());
        return ans;
    }

    vector<int> postOrder(Node *root)
    {
        vector<int> ans;
        if (!root)
        {
            return ans;
        }
        vector<int> left = postOrder(root->left);
        vector<int> right = postOrder(root->right);
        ans.insert(ans.end(), left.begin(), left.end());
        ans.insert(ans.end(), right.begin(), right.end());
        ans.push_back(root->data);
        return ans;
    }

    vector<vector<int>> levelOrder(Node *root)
    {
        vector<vector<int>> ans;
        if (!root)
        {
            return ans;
        }
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            int size = q.size();
            vector<int> level;
            for (int i = 0; i < size; i++)
            {
                Node *node = q.front();
                q.pop();
                if (node->left != NULL)
                {
                    q.push(node->left);
                }
                if (node->right != NULL)
                {
                    q.push(node->right);
                }
                level.push_back(node->data);
            }
            ans.push_back(level);
        }
        return ans;
    }

    bool isLeaf(Node *node)
    {
        if (node->left == NULL && node->right == NULL)
        {
            return true;
        }
        return false;
    }
    void addLeftBoundary(Node *root, vector<int> &ans)
    {
        Node *curr = root->left;
        while (curr)
        {
            if (!isLeaf(curr))
            {
                ans.push_back(curr->data);
            }
            if (curr->left)
            {
                curr = curr->left;
            }
            else
            {
                curr = curr->right;
            }
        }
    }
    void addLeafs(Node *root, vector<int> &ans)
    {
        if (isLeaf(root))
        {
            ans.push_back(root->data);
            return;
        }
        if (root->left)
        {
            addLeafs(root->left, ans);
        }
        if (root->right)
        {
            addLeafs(root->right, ans);
        }
    }
    void addRightBoundary(Node *root, vector<int> &ans)
    {
        Node *curr = root->right;
        vector<int> temp;
        while (curr)
        {
            if (!isLeaf(curr))
            {
                temp.push_back(curr->data);
            }
            if (curr->right)
            {
                curr = curr->right;
            }
            else
            {
                curr = curr->left;
            }
        }
        for (int i = temp.size() - 1; i >= 0; --i)
        {
            ans.push_back(temp[i]);
        }
    }
    vector<int> boundaryTraversal(Node *root)
    {
        vector<int> ans;
        if (!root)
        {
            return ans;
        }
        if (!isLeaf(root))
        {
            ans.push_back(root->data);
        }
        addLeftBoundary(root, ans);
        addLeafs(root, ans);
        addRightBoundary(root, ans);

        return ans;
    }

    vector<vector<int>> verticalOrder(Node *root)
    {

        // map: HD -> list of nodes
        map<int, vector<int>> mp;
        // queue: (node, HD)
        queue<pair<Node *, int>> q;

        q.push({root, 0});

        while (!q.empty())
        {
            auto [node, hd] = q.front();
            q.pop();

            mp[hd].push_back(node->data);

            if (node->left)
                q.push({node->left, hd - 1});
            if (node->right)
                q.push({node->right, hd + 1});
        }

        // Collect result
        vector<vector<int>> result;
        for (auto &p : mp)
        {
            result.push_back(p.second);
        }
        return result;

        // vector<vector<int>> ans;
        // if (!root)
        // {
        //     return ans;
        // }
        // map<int, map<int, multiset<int>>> nodes;
        // queue<pair<Node *, pair<int, int>>> todo;
        // todo.push({root, {0, 0}});
        // while (!todo.empty())
        // {
        //     auto temp = todo.front();
        //     todo.pop();
        //     Node *node = temp.first;
        //     int x = temp.second.first;
        //     int y = temp.second.second;
        //     nodes[x][y].insert(node->data);

        //     if (node->left)
        //     {
        //         todo.push({node->left, {x - 1, y + 1}});
        //     }
        //     if (node->right)
        //     {
        //         todo.push({node->right, {x + 1, y + 1}});
        //     }
        // }
        // for (auto temp : nodes)
        // {
        //     vector<int> col;
        //     for (auto q : temp.second)
        //     {
        //         col.insert(col.end(), q.second.begin(), q.second.end());
        //     }
        //     ans.push_back(col);
        // }
        // return ans;
    }

    vector<int> topView(Node *root)
    {
        vector<int> ans;
        if (!root)
        {
            return ans;
        }
        map<int, int> map;
        queue<pair<Node *, int>> q;
        q.push({root, 0});
        while (!q.empty())
        {
            auto temp = q.front();
            q.pop();
            Node *node = temp.first;
            int line = temp.second;
            if (map.find(line) == map.end())
            {
                map[line] = node->data;
            }
            if (node->left)
            {
                q.push({node->left, line - 1});
            }
            if (node->right)
            {
                q.push({node->right, line + 1});
            }
        }
        for (auto m : map)
        {
            ans.push_back(m.second);
        }
        return ans;
    }

    vector<int> bottomView(Node *root)
    {
        vector<int> ans;
        if (!root)
        {
            return ans;
        }
        map<int, int> map;
        queue<pair<Node *, int>> q;
        int size = q.size();
        q.push({root, 0});
        while (!q.empty())
        {
            auto temp = q.front();
            q.pop();
            Node *node = temp.first;
            int line = temp.second;
            map[line] = node->data;

            if (node->left)
            {
                q.push({node->left, line - 1});
            }
            if (node->right)
            {
                q.push({node->right, line + 1});
            }
        }
        for (auto m : map)
        {
            ans.push_back(m.second);
        }
        return ans;
    }

    vector<int> leftView(Node *root)
    {
        vector<int> ans;
        if (!root)
        {
            return ans;
        }
        map<int, int> map;
        queue<pair<Node *, int>> q;
        int size = q.size();
        q.push({root, 1});
        while (!q.empty())
        {
            auto temp = q.front();
            q.pop();
            Node *node = temp.first;
            int line = temp.second;
            if (map.find(line) == map.end())
            {
                map[line] = node->data;
            }

            if (node->left)
            {
                q.push({node->left, line + 1});
            }
            if (node->right)
            {
                q.push({node->right, line + 1});
            }
        }
        for (auto m : map)
        {
            ans.push_back(m.second);
        }
        return ans;
    }

    vector<int> rightView(Node *root)
    {
        vector<int> ans;
        if (!root)
        {
            return ans;
        }
        map<int, int> map;
        queue<pair<Node *, int>> q;
        int size = q.size();
        q.push({root, 1});
        while (!q.empty())
        {
            auto temp = q.front();
            q.pop();
            Node *node = temp.first;
            int line = temp.second;
            map[line] = node->data;

            if (node->left)
            {
                q.push({node->left, line + 1});
            }
            if (node->right)
            {
                q.push({node->right, line + 1});
            }
        }
        for (auto m : map)
        {
            ans.push_back(m.second);
        }
        return ans;
    }

    void rVRecurssion(Node *node, int level, vector<int> &ans)
    {
        if (!node)
        {
            return;
        }
        if (ans.size() == level)
        {
            ans.push_back(node->data);
        }
        rVRecurssion(node->right, level + 1, ans);
        rVRecurssion(node->left, level + 1, ans);
    }
    vector<int> rightViewRecurssion(Node *root)
    {
        vector<int> ans;
        rVRecurssion(root, 0, ans);
        return ans;
    }

    void lVRecurssion(Node *node, int level, vector<int> &ans)
    {
        if (!node)
        {
            return;
        }
        if (ans.size() == level)
        {
            ans.push_back(node->data);
        }
        lVRecurssion(node->left, level + 1, ans);
        lVRecurssion(node->right, level + 1, ans);
    }
    vector<int> leftViewRecurssion(Node *root)
    {
        vector<int> ans;
        lVRecurssion(root, 0, ans);
        return ans;
    }

    vector<int> diagonal(Node *root)
    {
        vector<int> ans;
        if (!root)
        {
            return ans;
        }
        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            Node *node = q.front();
            q.pop();

            while (node)
            {
                ans.push_back(node->data);
                if (node->left)
                {
                    q.push(node->left);
                }
                node = node->right;
            }
        }
        return ans;
    }

    void insertNodeInLeft(Node *root, Node *node)
    {
        if (root->left == NULL)
        {
            root->left = node;
            return;
        }
        insertNodeInLeft(root->left, node);
    }

    int height(Node *node)
    {
        if (!node)
        {
            return -1;
        }

        int l = height(node->left);
        int r = height(node->right);

        return 1 + max(l, r);
    }

    int diameterUtil(Node *node, int &maxDia)
    {
        if (!node)
        {
            return 0;
        }
        int l = diameterUtil(node->left, maxDia);
        int r = diameterUtil(node->right, maxDia);
        maxDia = max(maxDia, l + r);
        return 1 + max(l, r);
    }
    int diameter(Node *root)
    {
        int maxDia = 0;
        diameterUtil(root, maxDia);
        return maxDia;
    }

    bool isIdentical(Node *r1, Node *r2)
    {
        if (r1 == NULL || r2 == NULL)
        {
            return (r1 == r2);
        }

        return (r1->data == r2->data) && isIdentical(r1->left, r2->left) && isIdentical(r1->right, r2->right);
    }

    bool isSubTree(Node *T, Node *S)
    {
        if (S == NULL)
        {
            return true;
        }
        if (T == NULL)
        {
            return false;
        }
        if (isIdentical(T, S))
        {
            return true;
        }
        return isSubTree(T->left, S) || isSubTree(T->right, S);
    }

    int dfheight(Node *root)
    {
        if (!root)
        {
            return 0;
        }
        int lh = dfheight(root->left);
        if (lh == -1)
        {
            return -1;
        }
        int rh = dfheight(root->right);
        if (rh == -1)
        {
            return -1;
        }
        if (abs(lh - rh) > 1)
        {
            return -1;
        }
        return max(lh, rh) + 1;
    }
    bool isBalanced(Node *root)
    {
        return dfheight(root) != -1;
    }

    bool leftNodeValue(Node *root, int val)
    {
        if (!root)
        {
            return NULL;
        }
        Node *node = root;
        while (node)
        {
            if (node->data == val)
            {
                return true;
            }
            node = node->left;
        }
    }
    bool rightNodeValue(Node *root, int val)
    {
        if (!root)
        {
            return NULL;
        }
        Node *node = root;
        while (node)
        {
            if (node->data == val)
            {
                return true;
            }
            node = node->right;
        }
        return false;
    }

    Node *lca(Node *root, int n1, int n2)
    {
        if (root == NULL || root->data == n1 || root->data == n2)
        {
            return root;
        }

        Node *left = lca(root->left, n1, n2);
        Node *right = lca(root->right, n1, n2);

        if (left == NULL)
        {
            return right;
        }
        if (right == NULL)
        {
            return left;
        }
        else
        {
            return root;
        }
    }

    // Helper function that returns a pair: {isSumTree, sum of subtree}
    pair<bool, int> isSumTreeHelper(Node *root)
    {
        if (!root)
            return {true, 0};
        if (!root->left && !root->right)
            return {true, root->data};

        auto left = isSumTreeHelper(root->left);
        auto right = isSumTreeHelper(root->right);

        bool isCurrSumTree = left.first && right.first && (root->data == left.second + right.second);
        int totalSum = root->data + left.second + right.second;
        return {isCurrSumTree, totalSum};
    }
    bool isSumTree(Node *root)
    {
        return isSumTreeHelper(root).first;
    }

    bool isSymmetricHelper(Node *left, Node *right)
    {
        if (left == NULL || right == NULL)
        {
            return left == right;
        }
        if (left->data != right->data)
        {
            return false;
        }
        return isSymmetricHelper(left->left, right->right) && isSymmetricHelper(left->right, right->left);
    }
    bool isSymmetric(Node *root)
    {
        return root == NULL || isSymmetricHelper(root->left, root->right);
    }

    void mirror(Node *node)
    {
        if (!node)
        {
            return;
        }
        else
        {
            mirror(node->left);
            mirror(node->right);
            Node *temp;
            temp = node->left;
            node->left = node->right;
            node->right = temp;
        }
    }

    bool isIsomorphic(Node *root1, Node *root2)
    {
        if (root1 == NULL && root2 == NULL)
        {
            return true;
        }
        if (root1 == NULL || root2 == NULL)
        {
            return false;
        }
        if (root1->data != root2->data)
        {
            return false;
        }
        bool c1 = isIsomorphic(root1->left, root2->left) && isIsomorphic(root1->right, root2->right);
        bool c2 = isIsomorphic(root1->right, root2->left) && isIsomorphic(root1->left, root2->right);
        return c1 || c2;
    }

    void PathFind(Node *root, vector<int> &res, vector<vector<int>> &ans)
    {
        if (!root)
        {
            return;
        }
        res.push_back(root->data);
        if (root->left == NULL && root->right == NULL)
        {
            ans.push_back(res);
        }
        else
        {
            PathFind(root->left, res, ans);
            PathFind(root->right, res, ans);
        }
        res.pop_back();
    }
    vector<vector<int>> Paths(Node *root)
    {
        vector<vector<int>> ans;
        vector<int> res;
        PathFind(root, res, ans);
        return ans;
    }

    void PathFindSum(Node *root, vector<int> &ans, int sum)
    {
        if (!root)
        {
            return;
        }
        sum += root->data;
        if (root->left == NULL && root->right == NULL)
        {
            ans.push_back(sum);
        }
        else
        {
            PathFindSum(root->left, ans, sum);
            PathFindSum(root->right, ans, sum);
        }
    }
    vector<int> PathsSum(Node *root)
    {
        vector<int> ans;
        PathFindSum(root, ans, 0);
        return ans;
    }

    bool PathFindSumTarget(Node *root, int sum, int target)
    {
        if (!root)
        {
            return false;
        }
        sum += root->data;
        if (root->left == NULL && root->right == NULL)
        {
            return sum == target;
        }
        return PathFindSumTarget(root->left, sum, target) || PathFindSumTarget(root->right, sum, target);
    }
    bool hasPathSum(Node *root, int target)
    {
        return PathFindSumTarget(root, 0, target);
    }

    int findMaxSumUtil(Node *root, int &maxSum)
    {
        if (!root)
        {
            return 0;
        }
        int left = max(0, findMaxSumUtil(root->left, maxSum));
        int right = max(0, findMaxSumUtil(root->right, maxSum));
        maxSum = max(maxSum, root->data + left + right);
        return root->data + max(left, right);
    }
    int findMaxSum(Node *root)
    {
        int maxSum = INT_MIN;
        findMaxSumUtil(root, maxSum);
        return maxSum;
    }

    void findSumK2(Node *root, int k, long long currSum, unordered_map<long long, int> &prefix, int &ans)
    {
        if (!root)
        {
            return;
        }
        currSum += root->data;
        if (prefix.count(currSum - k))
        {
            ans += prefix[currSum - k];
        }
        prefix[currSum]++;
        findSumK2(root->left, k, currSum, prefix, ans);
        findSumK2(root->right, k, currSum, prefix, ans);
        prefix[currSum]--;
    }
    int sumK2(Node *root, int k)
    {
        unordered_map<long long, int> prefix;
        prefix[0] = 1;
        int ans = 0;
        findSumK2(root, k, 0, prefix, ans);
        return ans;
    }

    void findSumK(Node *root, vector<int> &path, int k, int &ans)
    {
        if (!root)
        {
            return;
        }
        path.push_back(root->data);

        findSumK(root->left, path, k, ans);
        findSumK(root->right, path, k, ans);

        int f = 0;

        for (int i = path.size() - 1; i >= 0; i--)
        {
            f += path[i];
            if (f == k)
            {
                ans += 1;
            }
        }
        path.pop_back();
    }
    int sumK(Node *root, int k)
    {
        vector<int> path;
        int ans = 0;
        findSumK(root, path, k, ans);
        return ans;
    }

    Node *findTargetNode(Node *root, int &target)
    {
        if (!root)
        {
            return nullptr;
        }
        if (root->data == target)
        {
            return root;
        }
        Node *leftResult = findTargetNode(root->left, target);
        if (leftResult)
        {
            return leftResult;
        }
        return findTargetNode(root->right, target);
    }
    void markParents(Node *root, unordered_map<Node *, Node *> &parent_track)
    {
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *curr = q.front();
            q.pop();
            if (curr->left)
            {
                parent_track[curr->left] = curr;
                q.push(curr->left);
            }
            if (curr->right)
            {
                parent_track[curr->right] = curr;
                q.push(curr->right);
            }
        }
    }
    vector<int> KDistanceNodes(Node *root, int target, int k)
    {
        unordered_map<Node *, Node *> parent_track;
        Node *targetNode = findTargetNode(root, target);
        markParents(root, parent_track);

        unordered_map<Node *, bool> visited;
        queue<Node *> q;
        int curr_level = 0;
        visited[targetNode] = true;
        q.push(targetNode);
        while (!q.empty())
        {
            int size = q.size();
            if (curr_level++ == k)
            {
                break;
            }
            for (int i = 0; i < size; i++)
            {
                Node *curr = q.front();
                q.pop();
                if (curr->left && !visited[curr->left])
                {
                    visited[curr->left] = true;
                    q.push(curr->left);
                }
                if (curr->right && !visited[curr->right])
                {
                    visited[curr->right] = true;
                    q.push(curr->right);
                }
                if (parent_track[curr] && !visited[parent_track[curr]])
                {
                    visited[parent_track[curr]] = true;
                    q.push(parent_track[curr]);
                }
            }
        }
        vector<int> res;
        while (!q.empty())
        {
            Node *temp = q.front();
            q.pop();
            res.push_back(temp->data);
        }
        sort(res.begin(), res.end());
        return res;
    }

    int getCount(Node *root, int l, int h)
    {
        if (!root)
            return 0;
        // If current node is in range, count it and check both subtrees
        if (root->data >= l && root->data <= h)
            return 1 + getCount(root->left, l, h) + getCount(root->right, l, h);
        // If current node is less than l, only check right subtree
        else if (root->data < l)
            return getCount(root->right, l, h);
        // If current node is greater than h, only check left subtree
        else
            return getCount(root->left, l, h);
    }

    int nodeSum(Node *root, int low, int high)
    {

        if (root == nullptr)
            return 0;

        // If root value is less than range.
        if (root->data < low)
        {
            return nodeSum(root->right, low, high);
        }

        // If root value is greater than range.
        else if (root->data > high)
        {
            return nodeSum(root->left, low, high);
        }

        // If root value lies in the range.
        int left = nodeSum(root->left, low, high);
        int right = nodeSum(root->right, low, high);

        return low + high + root->data;
    }

    int findLevel(Node *root, int val, int level)
    {
        if (!root)
            return -1;
        if (root->data == val)
            return level;
        int left = findLevel(root->left, val, level + 1);
        if (left != -1)
            return left;
        return findLevel(root->right, val, level + 1);
    }
    int findDist(Node *root, int a, int b)
    {
        Node *ancestor = lca(root, a, b);
        int d1 = findLevel(ancestor, a, 0);
        int d2 = findLevel(ancestor, b, 0);
        return d1 + d2;
    }

    int maxV(Node *root, int &maxVal)
    {
        if (!root)
        {
            return INT_MAX;
        }
        if (root->left == NULL && root->right == NULL)
        {
            return root->data;
        }
        int val = min(maxV(root->left, maxVal), maxV(root->right, maxVal));
        maxVal = max(maxVal, (root->data - val));

        return min(val, root->data);
    }
    int maxDiff(Node *root)
    {
        int maxVal = INT_MIN;
        maxV(root, maxVal);

        return maxVal;
    }

    int minTime(Node *root, int target)
    {
        unordered_map<Node *, Node *> parent_track;
        Node *targetNode = findTargetNode(root, target);
        markParents(root, parent_track);

        unordered_map<Node *, bool> visited;
        queue<Node *> q;
        q.push(targetNode);
        visited[targetNode] = true;
        int dis = -1;
        while (!q.empty())
        {
            int size = q.size();
            dis++;
            for (int i = 0; i < size; i++)
            {

                Node *curr = q.front();
                q.pop();
                if (curr->left && !visited[curr->left])
                {
                    q.push(curr->left);
                    visited[curr->left] = true;
                }
                if (curr->right && !visited[curr->right])
                {
                    q.push(curr->right);
                    visited[curr->right] = true;
                }
                if (parent_track[curr] && !visited[parent_track[curr]])
                {
                    q.push(parent_track[curr]);
                    visited[parent_track[curr]] = true;
                }
            }
        }
        return dis;
    }
};

int main()
{
    Node *root = new Node(1);      //            1
    Node *leftNode = new Node(2);  //         2      3
    Node *rightNode = new Node(3); //      4     5
    Node *leftNode2 = new Node(4);
    Node *rightNode2 = new Node(5);
    root->left = leftNode;
    root->right = rightNode;
    root->left->left = leftNode2;
    root->left->right = rightNode2;
    Tree t;

    // Node *newNode = new Node(40);
    // Node *newNode2 = new Node(100);
    // root->right->left = newNode;
    // root->right->right = newNode2;
    auto ans =
        t.KDistanceNodes(root, 2, 2);

    // cout << ans;
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

    // Free allocated memory
    delete leftNode2;
    // delete rightNode2;
    delete leftNode;
    delete rightNode;
    delete root;
    return 0;
}