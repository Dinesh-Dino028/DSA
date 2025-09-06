#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *next;

    Node(int val)
    {
        data = val;
        left = right = next = NULL;
    }
};

class BST
{
private:
public:
    vector<int> preOrder(Node *root)
    {
        vector<int> ans;
        if (!root)
        {
            return ans;
        }
        ans.push_back(root->data);
        vector<int> left = preOrder(root->left);
        vector<int> right = preOrder(root->right);
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

    void insertNodeRecur(Node *root, int val) // Recurssion method
    {
        if (!root)
        {
            return;
        }
        if (!root->left && val < root->data)
        {
            Node *newNode = new Node(val);
            root->left = newNode;
        }
        if (!root->right && val > root->data)
        {
            Node *newNode = new Node(val);
            root->right = newNode;
        }
        if (val < root->data)
        {
            insertNodeRecur(root->left, val);
        }
        else
        {
            insertNodeRecur(root->right, val);
        }
    }

    Node *insertNodeBST(Node *root, int val)
    {
        if (!root)
        {
            return new Node(val);
        }
        Node *curr = root;
        while (true)
        {
            if (curr->data <= val)
            {
                if (curr->right)
                {
                    curr = curr->right;
                }
                else
                {
                    curr->right = new Node(val);
                    break;
                }
            }
            else
            {
                if (curr->left)
                {
                    curr = curr->left;
                }
                else
                {
                    curr->left = new Node(val);
                    break;
                }
            }
        }
        return root;
    }

    bool search(Node *root, int x)
    {
        if (!root)
        {
            return false;
        }
        Node *curr = root;
        while (curr)
        {
            if (curr->data == x)
            {
                return true;
            }
            if (curr->data <= x)
            {
                if (curr->right)
                {
                    curr = curr->right;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                if (curr->left)
                {
                    curr = curr->left;
                }
                else
                {
                    return false;
                }
            }
        }
        return false;
    }

    bool search2(Node *root, int x)
    {
        while (root && root->data != x)
        {
            root = x < root->data ? root->left : root->right;
        }
        return root ? root->data == x ? true : false : false;
    }

    void findMaxVal(Node *root, int &maxVal)
    {
        if (!root)
        {
            return;
        }
        maxVal = max(maxVal, root->data);
        findMaxVal(root->right, maxVal);
        findMaxVal(root->left, maxVal);
    }
    int findMax(Node *root)
    {
        int maxVal = INT_MIN;
        findMaxVal(root, maxVal);
        return maxVal;
    }

    void findMinVal(Node *root, int &minVal)
    {
        if (!root)
        {
            return;
        }
        minVal = min(minVal, root->data);
        findMinVal(root->right, minVal);
        findMinVal(root->left, minVal);
    }
    int findMin(Node *root)
    {
        int minVal = INT_MAX;
        findMinVal(root, minVal);
        return minVal;
    }

    void kthLargestHelper(Node *root, int k, vector<int> &res)
    {
        if (!root)
        {
            return;
        }

        res.push_back(root->data);
        kthLargestHelper(root->right, k, res);
        kthLargestHelper(root->left, k, res);
        sort(res.begin(), res.end());
    }
    int kthLargest(Node *root, int k)
    {
        auto res =
            inOrder(root);
        return res[res.size() - k];
    }

    void reverseInorder(Node *root, int k, int &count, int &result)
    {
        if (!root || count >= k)
            return;

        // Visit right subtree first (larger values)
        reverseInorder(root->right, k, count, result);

        // Visit node
        count++;
        if (count == k)
        {
            result = root->data;
            return;
        }

        // Visit left subtree
        reverseInorder(root->left, k, count, result);
    }
    int kthLargest2(Node *root, int k)
    {
        int count = 0;
        int result = -1;
        reverseInorder(root, k, count, result);
        return result;
    }

    int getCount(Node *root, int l, int h)
    {
        if (!root)
            return 0;

        // if node value < l → check only right subtree
        if (root->data < l)
            return getCount(root->right, l, h);

        // if node value > h → check only left subtree
        if (root->data > h)
            return getCount(root->left, l, h);

        // node value lies in range → count it and check both sides
        return 1 + getCount(root->left, l, h) + getCount(root->right, l, h);
    }

    Node *lca(Node *root, int n1, int n2)
    {
        if (!root)
        {
            return NULL;
        }
        int curr = root->data;
        if (curr < n1 && curr < n2)
        {
            return lca(root->right, n1, n2);
        }
        if (curr > n1 && curr > n2)
        {
            return lca(root->left, n1, n2);
        }
        return root;
    }

    bool isBSTUtil(Node *root, int minVal, int maxVal)
    {
        if (!root)
            return true;
        if (root->data <= minVal || root->data >= maxVal)
            return false;
        return isBSTUtil(root->left, minVal, root->data) &&
               isBSTUtil(root->right, root->data, maxVal);
    }
    bool isBST(Node *root)
    {
        return isBSTUtil(root, INT_MIN, INT_MAX);
    }

    void minDiffHelper(Node *root, int K, int &ans)
    {
        if (!root)
        {
            return;
        }
        ans = min(ans, abs(root->data - K));
        if (K < root->data)
        {
            minDiffHelper(root->left, K, ans);
        }
        else
        {
            minDiffHelper(root->right, K, ans);
        }
    }
    int minDiff(Node *root, int K)
    {
        int ans = INT_MAX;

        minDiffHelper(root, K, ans);
        return ans;
    }

    struct Info
    {
        bool isBST;
        int size;
        int minVal;
        int maxVal;
    };
    Info largestBSTHelper(Node *root, int &maxSize)
    {
        if (!root)
        {
            return {true, 0, INT_MAX, INT_MIN};
        }
        Info left = largestBSTHelper(root->left, maxSize);
        Info right = largestBSTHelper(root->right, maxSize);
        Info curr;
        curr.size = left.size + right.size + 1;
        if (left.isBST && right.isBST && root->data > left.maxVal && root->data < right.minVal)
        {
            curr.isBST = true;
            curr.minVal = min(root->data, left.minVal);
            curr.maxVal = max(root->data, right.maxVal);
            maxSize = max(maxSize, curr.size);
        }
        else
        {
            curr.isBST = false;
        }
        return curr;
    }
    int largestBst(Node *root)
    {
        int maxSize = 0;
        largestBSTHelper(root, maxSize);
        return maxSize;
    }

    Node *LCA(Node *root, Node *n1, Node *n2)
    {
        return lca(root, n1->data, n2->data);
    }

    vector<int> mergeSortedArrays(vector<int> r1, vector<int> r2)
    {
        vector<int> ans;
        int i = 0, j = 0;

        while (i < r1.size() && j < r2.size())
        {
            if (r1[i] < r2[j])
            {
                ans.push_back(r1[i++]);
            }
            else
            {
                ans.push_back(r2[j++]);
            }
        }
        while (i < r1.size())
        {
            ans.push_back(r1[i++]);
        }
        while (j < r2.size())
        {
            ans.push_back(r2[j++]);
        }
        return ans;
    }
    vector<int> merge(Node *root1, Node *root2)
    {
        vector<int> r1, r2;
        r1 = inOrder(root1);
        r2 = inOrder(root2);

        return mergeSortedArrays(r1, r2);
    }

    vector<int> findPreSucHelperInorder(Node *root, int key, int &successor, int &predecessor)
    {
        vector<int> ans;
        if (!root)
        {
            return ans;
        }

        vector<int> left = findPreSucHelperInorder(root->left, key, successor, predecessor);
        vector<int> right = findPreSucHelperInorder(root->right, key, successor, predecessor);

        ans.insert(ans.end(), left.begin(), left.end());

        ans.push_back(root->data);
        ans.insert(ans.end(), right.begin(), right.end());
        return ans;
    }
    vector<Node *> findPreSuc(Node *root, int key)
    {
        Node *pred = NULL;
        Node *succ = NULL;
        Node *curr = root;

        // Find predecessor (largest value less than key)
        while (curr)
        {
            if (curr->data < key)
            {
                pred = curr;
                curr = curr->right;
            }
            else
            {
                curr = curr->left;
            }
        }

        curr = root;
        // Find successor (smallest value greater than key)
        while (curr)
        {
            if (curr->data > key)
            {
                succ = curr;
                curr = curr->left;
            }
            else
            {
                curr = curr->right;
            }
        }

        return {pred, succ};
    }

    void populateNextHelper(Node *root, Node *&prev)
    {
        if (!root)
            return;

        // Reverse inorder traversal: Right -> Root -> Left
        populateNextHelper(root->right, prev);

        // Set the next of current node to previously visited node
        root->next = prev;

        // Update prev to current node
        prev = root;

        populateNextHelper(root->left, prev);
    }
    void populateNext(Node *root)
    {
        Node *prev = NULL;
        populateNextHelper(root, prev);
    }

    void transformTreeHelper(Node *root, int &currSum)
    {
        if (!root)
        {
            return;
        }
        transformTreeHelper(root->right, currSum);
        int temp = root->data;
        root->data = currSum;
        currSum += temp;
        transformTreeHelper(root->left, currSum);
    }
    void transformTree(struct Node *root)
    {
        int currSum = 0;
        transformTreeHelper(root, currSum);
    }

    Node *findLastRight(Node *root)
    {
        if (!root->right)
        {
            return root;
        }
        return findLastRight(root->right);
    }
    Node *deleteNodeHelper(Node *root)
    {
        if (!root->left)
        {
            return root->right;
        }
        else if (!root->right)
        {
            return root->left;
        }
        Node *rightChild = root->right;
        Node *lastRight = findLastRight(root->left);
        lastRight->right = rightChild;
        return root->left;
    }
    Node *deleteNode(Node *root, int key)
    {
        if (!root)
        {
            return root;
        }
        if (root->data == key)
        {
            return deleteNodeHelper(root);
        }

        Node *dummy = root;
        while (root)
        {
            if (key < root->data)
            {
                if (root->left && root->left->data == key)
                {
                    root->left = deleteNodeHelper(root->left);
                }
                else
                {
                    root = root->left;
                }
            }
            else
            {
                if (root->right && root->right->data == key)
                {
                    root->right = deleteNodeHelper(root->right);
                }
                else
                {
                    root = root->right;
                }
            }
        }
        return dummy;
    }

    Node *buildTree(const vector<int> &preorder, int preStart, int preEnd, const vector<int> &inorder, int inStart, int inEnd, const map<int, int> &inMap)
    {
        if (preStart > preEnd || inStart > inEnd)
        {
            return NULL;
        }
        Node *root = new Node(preorder[preStart]);
        int inRoot = inMap.at(root->data);
        int numsLeft = inRoot - inStart;

        root->left = buildTree(preorder, preStart + 1, preStart + numsLeft, inorder, inStart, inRoot - 1, inMap);

        root->right = buildTree(preorder, preStart + numsLeft + 1, preEnd, inorder, inRoot + 1, inEnd, inMap);

        return root;
    }
    Node *buildTree(vector<int> &inorder, vector<int> &preorder)
    {
        map<int, int> inMap;
        for (int i = 0; i < inorder.size(); i++)
        {
            inMap[inorder[i]] = i;
        }
        Node *root = buildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1, inMap);
        return root;
    }

    Node *buildTreeFromPost(const vector<int> &postorder, int postStart, int postEnd, const vector<int> &inorder, int inStart, int inEnd, const map<int, int> &inMap)
    {
        if (postStart > postEnd || inStart > inEnd)
        {
            return NULL;
        }
        Node *root = new Node(postorder[postEnd]);
        int inRoot = inMap.at(root->data);
        int numsRight = inEnd - inRoot;
        root->right = buildTreeFromPost(postorder, postEnd - numsRight, postEnd - 1, inorder, inRoot + 1, inEnd, inMap);
        root->left = buildTreeFromPost(postorder, postStart, postEnd - numsRight - 1, inorder, inStart, inRoot - 1, inMap);

        return root;
    }
    Node *buildTreeFromPost(vector<int> &inorder, vector<int> &postorder)
    {
        map<int, int> inMap;
        for (int i = 0; i < inorder.size(); i++)
        {
            inMap[inorder[i]] = i;
        }
        Node *root = buildTreeFromPost(postorder, 0, postorder.size() - 1, inorder, 0, inorder.size() - 1, inMap);
        return root;
    }

    Node *constructTreeUntil(int n, int pre[], char preLN[], int &index)
    {
        if (index >= n)
        {
            return NULL;
        }

        Node *root = new Node(pre[index]);
        if (preLN[index++] == 'L')
        {
            return root;
        }

        root->left = constructTreeUntil(n, pre, preLN, index);
        root->right = constructTreeUntil(n, pre, preLN, index);
        return root;
    }
    struct Node *constructTree(int n, int pre[], char preLN[])
    {
        int index = 0;
        return constructTreeUntil(n, pre, preLN, index);
    }

    Node *createTree(vector<int> parent)
    {
        int n = parent.size();
        vector<Node *> nodes(n, NULL);

        Node *root = NULL;
        for (int i = 0; i < n; i++)
        {
            nodes[i] = new Node(i);
        }

        for (int i = 0; i < n; i++)
        {
            if (parent[i] == -1)
            {
                root = nodes[i];
            }
            else
            {
                Node *p = nodes[parent[i]];
                if (p->left == NULL)
                {
                    p->left = nodes[i];
                }
                else
                {
                    p->right = nodes[i];
                }
            }
        }
        return root;
    }

    vector<int> serialize(Node *root)
    {
        vector<int> res;
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *temp = q.front();
            q.pop();
            if (!temp)
            {
                res.push_back(INT_MAX);
            }
            else
            {
                res.push_back(temp->data);
            }
            if (temp)
            {
                q.push(temp->left);
                q.push(temp->right);
            }
        }
        return res;
    }

    // Function to deserialize a list and construct the tree.
    Node *deSerialize(vector<int> &arr)
    {
        if (arr.empty())
            return NULL;
        int n = arr.size();
        int i = 0;
        Node *root = new Node(arr[i++]);
        queue<Node *> q;
        q.push(root);
        while (!q.empty() && i < n)
        {
            Node *curr = q.front();
            q.pop();
            // left child
            if (i < n)
            {
                if (arr[i] != INT_MAX)
                {
                    curr->left = new Node(arr[i]);
                    q.push(curr->left);
                }
                else
                {
                    curr->left = NULL;
                }
                i++;
            }
            // right child
            if (i < n)
            {
                if (arr[i] != INT_MAX)
                {
                    curr->right = new Node(arr[i]);
                    q.push(curr->right);
                }
                else
                {
                    curr->right = NULL;
                }
                i++;
            }
        }
        return root;
    }

    int findLargestSubtreeSumHelper(Node *root, int &maxSum)
    {
        if (!root)
        {
            return 0;
        }
        int left_sum = findLargestSubtreeSumHelper(root->left, maxSum);
        int right_sum = findLargestSubtreeSumHelper(root->right, maxSum);
        int current_sum = root->data + left_sum + right_sum;
        maxSum = max(maxSum, current_sum);
        return current_sum;
    }

    int findLargestSubtreeSum(Node *root)
    {
        int maxSum = INT_MIN;
        findLargestSubtreeSumHelper(root, maxSum);
        return maxSum;
    }

    string printAllDupsHelper(Node *root, unordered_map<string, int> &mp, vector<Node *> &result)
    {
        if (!root)
        {
            return "#";
        }
        string left = printAllDupsHelper(root->left, mp, result);
        string right = printAllDupsHelper(root->right, mp, result);
        string serial = "(" + left + to_string(root->data) + right + ")";
        if (mp[serial] == 1)
        {
            result.push_back(root);
        }
        mp[serial]++;
        return serial;
    }
    vector<Node *> printAllDups(Node *root)
    {
        vector<Node *> res;
        unordered_map<string, int> mp;
        printAllDupsHelper(root, mp, res);
        return res;
    }

    void flattenHelper(Node *root, Node *&prev)
    {
        if (!root)
        {
            return;
        }
        flattenHelper(root->right, prev);
        flattenHelper(root->left, prev);
        root->right = prev;
        root->left = NULL;

        prev = root;
    }

    void flatten(Node *root)
    {
        Node *prev = NULL;
        flattenHelper(root, prev);
    }
    pair<int, int> dfs(Node *root)
    {
        if (!root)
            return {0, 0}; // {include, exclude}

        auto left = dfs(root->left);
        auto right = dfs(root->right);

        int include = root->data + left.second + right.second;
        int exclude = max(left.first, left.second) + max(right.first, right.second);

        return {include, exclude};
    }
    int getMaxSum(Node *root)
    {
        auto res = dfs(root);
        return max(res.first, res.second);
    }

};

int main()
{
    BST bs;

    Node *root = new Node(5);      //       5
    Node *leftNode = new Node(3);  //    3     7
    Node *rightNode = new Node(7); // 2     4
    Node *leftNode2 = new Node(2);
    Node *rightNode2 = new Node(4);

    // Node *newNode1 = new Node(4);
    // Node *newNode2 = new Node(7);
    // Node *newNode3 = new Node(14);
    // Node *newNode4 = new Node(1);

    root->left = leftNode;
    root->right = rightNode;
    root->left->left = leftNode2;
    root->left->right = rightNode2;

    // root->left->right->left = newNode1;
    // root->left->right->right = newNode2;

    // root->right->right = newNode3;
    // root->right->right->left = newNode4;

    vector<int> inorder = {-1, 0, 0, 1, 1, 3, 5};
    vector<int> postorder = {9, 15, 7, 20, 3};

    //auto ans = 
    bs.transformTree(root);
    // auto res =
    //     bs.deSerialize(arr);
    //cout << ans;
    // auto ans =
    //     bs.inOrder(res);

    // for (auto a : ans)
    // {
    //     cout << a->data << " ";
    // }
    return 0;
}