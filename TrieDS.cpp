#include <bits/stdc++.h>
using namespace std;

struct TrieNode
{
public:
    bool isEnd;
    unordered_map<char, TrieNode *> children;
    int wordCount;
    TrieNode()
    {
        isEnd = false;
        wordCount = 0;
    }
};

class TrieDS
{
private:
    TrieNode *root;

public:
    /** Initialize your data structure here. */
    TrieDS()
    {
        root = new TrieNode();
    }

    /** Inserts a word into the trie. */
    void insert(string word)
    {
        TrieNode *node = root;
        for (auto c : word)
        {
            if (!node->children[c])
            {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEnd = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word)
    {
        TrieNode *node = root;
        for (char c : word)
        {
            if (!node->children[c])
            {
                return false;
            }
            node = node->children[c];
        }
        return node->isEnd;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix)
    {
        TrieNode *node = root;
        for (char c : prefix)
        {
            if (!node->children[c])
            {
                return false;
            }
            node = node->children[c];
        }
        return true;
    }
};

// Trie Problem

class TrieNode2
{
public:
    int childCount;
    bool isEnd;
    TrieNode2 *children[26];
    TrieNode2()
    {
        isEnd = false;
        childCount = 0;
        memset(children, 0, sizeof(children));
    }
};

class Trie2
{
public:
    TrieNode2 *root;
    Trie2() { root = new TrieNode2(); }

    void insert(const string &word)
    {
        TrieNode2 *node = root;
        for (char c : word)
        {
            int idx = c - 'a';
            if (!node->children[idx])
            {
                node->children[idx] = new TrieNode2();
                node->childCount++;
            }
            node = node->children[idx];
        }
        node->isEnd = true;
    }

    string getLongestCommonPrefix()
    {
        string prefix = "";
        TrieNode2 *node = root;

        while (node && node->childCount == 1 && !node->isEnd)
        {
            for (int i = 0; i < 26; i++)
            {
                if (node->children[i])
                {
                    prefix.push_back('a' + i);
                    node = node->children[i];
                    break;
                }
            }
        }
        return prefix;
    }
};

struct TrieNode3
{
    TrieNode3 *child[2];
    bool isEnd;

    TrieNode3()
    {
        child[0] = child[1] = nullptr;
        isEnd = false;
    }
};

class Solution
{
public:
#define MAX 1000
    TrieNode3 *root = new TrieNode3();
    bool insert(int *row, int col)
    {
        TrieNode3 *node = root;
        for (int i = 0; i < col; i++)
        {
            int val = row[i];
            if (node->child[val] == nullptr)
            {
                node = new TrieNode3();
            }
            node = node->child[val];
        }
        if (node->isEnd)
        {
            return false; // already exists
        }
        node->isEnd = true;
        return true; // new row
    }

    string longestCommonPrefix(vector<string> &strs)
    {
        if (strs.empty())
            return "";

        Trie2 trie;
        for (auto &word : strs)
            trie.insert(word);

        return trie.getLongestCommonPrefix();
    }

    vector<vector<int>> uniqueRow(int M[MAX][MAX], int row, int col)
    {
        vector<vector<int>> result;
        for (int i = 0; i < row; ++i)
        {
            if (insert(M[i], col))
            {
                vector<int> temp;
                for (int j = 0; j < col; ++j)
                {
                    temp.push_back(M[i][j]);
                }
                result.push_back(temp);
            }
        }
        return result;
    }
};

int main()
{
    TrieDS trie;
    // trie.insert("apple");
    // trie.insert("app");

    // cout << trie.search("apple") << endl;   // 1 (true)
    // cout << trie.search("appl") << endl;    // 0 (false)
    // cout << trie.startsWith("app") << endl; // 1 (true)
    // cout << trie.search("app") << endl;     // 1 (true)

    Solution s;
    vector<string> strs = {"flower", "flow", "flight"};

    int M[MAX][MAX] = {{1, 1, 0, 1}, {1, 0, 0, 1}, {1, 1, 0, 1}};
    auto ans = s.uniqueRow(M, 3, 4);
    for (auto a : ans)
    {
        for (auto b : a)
        {
            cout << b << " ";
        }
        cout << endl;
    }
    return 0;
}
