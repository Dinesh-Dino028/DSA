#include <bits/stdc++.h>
using namespace std;

class Backtracking
{
private:
public:
    void recurPermutation(vector<char> &ds, string &s, vector<string> &ans, vector<int> &freq)
    {
        if (ds.size() == s.size())
        {
            ans.push_back(string(ds.begin(), ds.end()));
            return;
        }

        for (int i = 0; i < s.length(); i++)
        {
            if (i > 0 && s[i] == s[i - 1] && !freq[i - 1])
                continue;
            if (!freq[i])
            {
                ds.push_back(s.at(i));
                freq[i] = 1;
                recurPermutation(ds, s, ans, freq);
                freq[i] = 0;
                ds.pop_back();
            }
        }
    }
    vector<string> findPermutation(string &s)
    {
        vector<string> ans;
        vector<char> ds;

        sort(s.begin(), s.end());
        vector<int> freq(s.size(), 0);
        recurPermutation(ds, s, ans, freq);
        return ans;
    }

    void recurPermuteUnique(vector<int> &ds, const vector<int> &nums, vector<vector<int>> &res, map<int, int> &mp)
    {
        if (ds.size() == nums.size())
        {
            res.push_back(ds);
            return;
        }

        for (auto &p : mp)
        {
            if (p.second > 0)
            {
                ds.push_back(p.first);
                p.second -= 1;
                recurPermuteUnique(ds, nums, res, mp);
                p.second += 1;
                ds.pop_back();
            }
        }
    }
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        vector<vector<int>> res;
        vector<int> ds;
        map<int, int> mp;
        for (int i = 0; i < nums.size(); i++)
        {
            mp[nums[i]]++;
        }
        recurPermuteUnique(ds, nums, res, mp);
        return res;
    }

    void recurCombinationSum(int index, vector<int> &arr, int target, vector<vector<int>> &ans, vector<int> &ds)
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
            recurCombinationSum(index, arr, target - arr[index], ans, ds);
            ds.pop_back();
        }
        recurCombinationSum(index + 1, arr, target, ans, ds);
    }
    vector<vector<int>> combinationSum(vector<int> &arr, int target)
    {
        vector<vector<int>> ans;
        vector<int> ds;
        recurCombinationSum(0, arr, target, ans, ds);
        return ans;
    }

    void recurCombinationSum2(int index, vector<int> &candidates, int target, vector<vector<int>> &ans, vector<int> &ds)
    {
        if (target == 0)
        {
            ans.push_back(ds);
            return;
        }
        for (int i = index; i < candidates.size(); i++)
        {
            if (i > index && candidates[i] == candidates[i - 1])
            {
                continue;
            }
            if (candidates[i] > target)
            {
                break;
            }

            ds.push_back(candidates[i]);
            recurCombinationSum2(i + 1, candidates, target - candidates[i], ans, ds);
            ds.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> ans;
        vector<int> ds;
        recurCombinationSum2(0, candidates, target, ans, ds);
        return ans;
    }

    void recurCombinationSum3(int index, int &size, vector<int> &arr, int target, vector<vector<int>> &ans, vector<int> &ds)
    {
        if (target == 0)
        {
            if (ds.size() == size)
            {
                ans.push_back(ds);
            }
            return;
        }

        for (int i = index; i < arr.size(); i++)
        {
            if (i > 0 && arr[i] == arr[i - 1])
            {
                continue;
            }
            if (arr[i] > target)
            {
                break;
            }
            ds.push_back(arr[i]);
            recurCombinationSum3(i + 1, size, arr, target - arr[i], ans, ds);
            ds.pop_back();
        }
    }
    vector<vector<int>> combinationSum3(int k, int n)
    {
        vector<vector<int>> ans;
        if (k > n)
        {
            return ans;
        }
        vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        vector<int> ds;
        recurCombinationSum3(0, k, arr, n, ans, ds);
        return ans;
    }

    void solve(int i, int j, vector<vector<int>> &m, int n, vector<string> &ans, string move, vector<vector<int>> &vis, int di[], int dj[])
    {
        if (i == n - 1 && j == n - 1)
        {
            ans.push_back(move);
            return;
        }

        string dir = "DLRU";
        for (int ind = 0; ind < 4; ind++)
        {
            int nexti = i + di[ind];
            int nextj = j + dj[ind];
            if (nexti >= 0 && nextj >= 0 && nexti < n && nextj < n && !vis[nexti][nextj] && m[nexti][nextj] == 1)
            {
                vis[i][j] = 1;
                solve(nexti, nextj, m, n, ans, move + dir[ind], vis, di, dj);
                vis[i][j] = 0;
            }
        }
    }
    vector<string> ratInMaze(vector<vector<int>> &maze)
    {
        int n = maze.size();
        vector<string> ans;
        vector<vector<int>> vis(n, vector<int>(n, 0));
        int di[] = {+1, 0, 0, -1};
        int dj[] = {0, -1, 1, 0};
        if (maze[0][0] == 1)
        {
            solve(0, 0, maze, n, ans, "", vis, di, dj);
        }
        return ans;
    }

    void recurPossibleWords(int index, vector<int> &arr, string current, vector<string> &ans)
    {
        if (index == arr.size())
        {
            ans.push_back(current);
            return;
        }
        vector<string> mapping = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        int digit = arr[index];
        for (char ch : mapping[digit])
        {
            recurPossibleWords(index + 1, arr, current + ch, ans);
        }
    }
    vector<string> possibleWords(vector<int> &arr)
    {
        vector<string> ans;
        if (arr.empty())
            return ans;
        recurPossibleWords(0, arr, "", ans);
        return ans;
    }

    void recurSubsets(int index, vector<int> &arr, vector<int> &current, vector<vector<int>> &ans)
    {
        ans.push_back(current);
        for (int i = index; i < arr.size(); i++)
        {
            current.push_back(arr[i]);
            recurSubsets(i + 1, arr, current, ans);
            current.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int> &arr)
    {
        vector<vector<int>> ans;
        vector<int> current;
        sort(arr.begin(), arr.end());
        recurSubsets(0, arr, current, ans);
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
            current.push_back(arr[i]);
            recurAllSubsets(i + 1, arr, current, n, ans);
            current.pop_back();
        }
    }
    vector<vector<int>> AllSubsets(vector<int> arr, int n)
    {
        vector<vector<int>> ans;
        vector<int> current;
        sort(arr.begin(), arr.end());
        recurAllSubsets(0, arr, current, n, ans);
        return ans;
    }

    void solvenQueen(int col, vector<vector<int>> &ans, vector<int> &board, vector<int> &leftRow, vector<int> &upperDiagonal, vector<int> &lowerDiagonal, int &n)
    {
        if (col >= n)
        {
            ans.push_back(board);
            return;
        }

        for (int row = 0; row < n; row++)
        {
            if (leftRow[row] == 0 && lowerDiagonal[row + col] == 0 && upperDiagonal[n - 1 + col - row] == 0)
            {
                board.push_back(row + 1);
                leftRow[row] = 1;
                lowerDiagonal[row + col] = 1;
                upperDiagonal[n - 1 + col - row] = 1;
                solvenQueen(col + 1, ans, board, leftRow, upperDiagonal, lowerDiagonal, n);
                board.pop_back();
                leftRow[row] = 0;
                lowerDiagonal[row + col] = 0;
                upperDiagonal[n - 1 + col - row] = 0;
            }
        }
    }
    vector<vector<int>> nQueen(int n)
    {
        vector<vector<int>> ans;
        vector<int> board;
        vector<int> leftRow(n, 0);
        vector<int> upperDiagonal(2 * n - 1, 0);
        vector<int> lowerDiagonal(2 * n - 1, 0);

        solvenQueen(0, ans, board, leftRow, upperDiagonal, lowerDiagonal, n);
        return ans;
    }

    void solvetotalNQueens(int col, int &ans, vector<int> &board, vector<int> &leftRow, vector<int> &upperDiagonal, vector<int> &lowerDiagonal, int &n)
    {
        if (col >= n)
        {
            ans++;
            return;
        }
        for (int row = 0; row < n; row++)
        {
            if (leftRow[row] == 0 && lowerDiagonal[row + col] == 0 && upperDiagonal[n - 1 + col - row] == 0)
            {
                board.push_back(row + 1);
                leftRow[row] = 1;
                lowerDiagonal[row + col] = 1;
                upperDiagonal[n - 1 + col - row] = 1;
                solvetotalNQueens(col + 1, ans, board, leftRow, upperDiagonal, lowerDiagonal, n);
                board.pop_back();
                leftRow[row] = 0;
                lowerDiagonal[row + col] = 0;
                upperDiagonal[n - 1 + col - row] = 0;
            }
        }
    }
    int totalNQueens(int n)
    {
        int ans = 0;
        vector<int> board;
        vector<int> leftRow(n, 0);
        vector<int> upperDiagonal(2 * n - 1, 0);
        vector<int> lowerDiagonal(2 * n - 1, 0);

        solvetotalNQueens(0, ans, board, leftRow, upperDiagonal, lowerDiagonal, n);
        return ans;
    }

    void permutationHelper(int index, vector<string> &ans, string str, string &s)
    {
        if (index == s.size() - 1)
        {
            str += s[index];
            ans.push_back(str);
            return;
        }
        permutationHelper(index + 1, ans, str + s[index] + " ", s);
        permutationHelper(index + 1, ans, str + s[index], s);
    }
    vector<string> permutation(string s)
    {
        vector<string> ans;
        string str = "";
        permutationHelper(0, ans, str, s);
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
        int n = s.length();
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
    string generateIpAdd(string &s, int i, int j, int k, int n)
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
        // code here
        vector<string> ans;
        int n = s.length();
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                for (int k = j + 1; k < n; k++)
                {
                    string str = generateIpAdd(s, i, j, k, n);
                    if (str.length() > 0)
                    {
                        ans.push_back(str);
                    }
                }
            }
        }

        return ans;
    }

    bool isValid(vector<vector<int>> &board, int row, int col, int k)
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
            if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == k)
            {
                return false;
            }
        }
        return true;
    }
    bool recurSolveSudoku(vector<vector<int>> &board)
    {
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                if (board[i][j] == 0)
                {
                    for (int k = 1; k <= 9; k++)
                    {
                        if (isValid(board, i, j, k))
                        {
                            board[i][j] = k;
                            if (recurSolveSudoku(board) == true)
                            {
                                return true;
                            }
                            else
                            {
                                board[i][j] = 0;
                            }
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    void solveSudoku(vector<vector<int>> &mat)
    {
        recurSolveSudoku(mat);
    }

    string kthPermutation(int n, int k)
    {
        int fact = 1;
        vector<int> numbers;
        for (int i = 1; i < n; i++)
        {
            fact = fact * i;
            numbers.push_back(i);
        }
        numbers.push_back(n);
        string ans = "";
        k = k - 1;
        while (true)
        {
            ans = ans + to_string(numbers[k / fact]);
            numbers.erase(numbers.begin() + k / fact);
            if (numbers.size() == 0)
            {
                break;
            }
            k = k % fact;
            fact = fact / numbers.size();
        }
        return ans;
    }

    bool isPalindrome(string &s, int start, int end)
    {
        while (start <= end)
        {
            if (s[start++] != s[end--])
            {
                return false;
            }
        }
        return true;
    }
    void recurPalinParts(int index, string &s, vector<string> &current, vector<vector<string>> &ans)
    {
        if (index == s.size())
        {
            ans.push_back(current);
            return;
        }

        for (int i = index; i < s.size(); ++i)
        {
            if (isPalindrome(s, index, i))
            {
                current.push_back(s.substr(index, i - index + 1));
                recurPalinParts(i + 1, s, current, ans);
                current.pop_back();
            }
        }
    }
    vector<vector<string>> palinParts(string &s)
    {
        // code here
        vector<vector<string>> ans;
        vector<string> current;
        recurPalinParts(0, s, current, ans);
        return ans;
    }

    string decodedString(string &s)
    {
        stack<int> counts;
        stack<string> resultStack;
        string result = "";
        int i = 0;
        while (i < s.size())
        {
            if (isdigit(s[i]))
            {
                int count = 0;
                while (i < s.size() && isdigit(s[i]))
                {
                    count = count * 10 + (s[i] - '0');
                    i++;
                }
                counts.push(count);
            }
            else if (s[i] == '[')
            {
                resultStack.push(result);
                result = "";
                i++;
            }
            else if (s[i] == ']')
            {
                string temp = resultStack.top();
                resultStack.pop();
                int repeatTimes = counts.top();
                counts.pop();
                for (int j = 0; j < repeatTimes; j++)
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

    void recurletterCasePermutation(int index, string &s, string &ds, vector<string> &res)
    {
        if (index == s.size())
        {
            res.push_back(ds);
            return;
        }

        if (isalpha(s[index]))
        {
            // to lower branch
            ds.push_back(tolower(s[index]));
            recurletterCasePermutation(index + 1, s, ds, res);
            ds.pop_back();
            // to upper branch
            ds.push_back(toupper(s[index]));
            recurletterCasePermutation(index + 1, s, ds, res);
            ds.pop_back();
        }
        else
        {
            ds.push_back(s[index]);
            recurletterCasePermutation(index + 1, s, ds, res);
            ds.pop_back();
        }
    }
    vector<string> letterCasePermutation(string s)
    {
        vector<string> res;
        string ds;
        recurletterCasePermutation(0, s, ds, res);
        return res;
    }

    bool isSumStringUtil(string &s, int start, int len1, int len2)
    {
        // Avoid leading zeros unless the number is '0'
        if ((s[start] == '0' && len1 > 1) || (s[start + len1] == '0' && len2 > 1))
            return false;
        string s1 = s.substr(start, len1);
        string s2 = s.substr(start + len1, len2);
        string sum;
        // Add two numbers as strings to avoid overflow
        int i = s1.size() - 1, j = s2.size() - 1, carry = 0;
        while (i >= 0 || j >= 0 || carry)
        {
            int n1 = i >= 0 ? s1[i--] - '0' : 0;
            int n2 = j >= 0 ? s2[j--] - '0' : 0;
            int total = n1 + n2 + carry;
            sum.push_back((total % 10) + '0');
            carry = total / 10;
        }
        reverse(sum.begin(), sum.end());
        int sumLen = sum.size();
        int nextPos = start + len1 + len2;
        if (nextPos + sumLen > s.size() || s.substr(nextPos, sumLen) != sum)
            return false;
        if (nextPos + sumLen == s.size())
            return true;
        return isSumStringUtil(s, start + len1, len2, sumLen);
    }

    bool isSumString(string &s)
    {
        int n = s.size();
        // Try all possible first and second number lengths
        for (int len1 = 1; len1 <= n / 2; ++len1)
        {
            for (int len2 = 1; len2 <= (n - len1) / 2; ++len2)
            {
                if (isSumStringUtil(s, 0, len1, len2))
                    return true;
            }
        }
        return false;
    }

    bool dfs(int i, int j, vector<vector<char>> &board, string &word, int index, vector<vector<bool>> &visited)
    {
        if (index == word.size())
        {
            return true;
        }
        int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1};
        int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};
        int n = board.size();
        int m = board[0].size();
        if (i < 0 || j < 0 || i >= n || j >= m || visited[i][j] || board[i][j] != word[index])
        {
            return false;
        }
        visited[i][j] = true;

        for (int dir = 0; dir < 8; dir++)
        {
            if (dfs(i + dx[dir], j + dy[dir], board, word, index + 1, visited))
            {
                visited[i][j] = false;
                return true;
            }
        }
        visited[i][j] = false;
        return false;
    }
    bool exist(vector<vector<char>> &board, string &word)
    {
        int n = board.size();
        int m = board[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (board[i][j] == word[0])
                {
                    if (dfs(i, j, board, word, 0, visited))
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    vector<string> wordBoggle(vector<vector<char>> &board, vector<string> &dictionary)
    {
        // Code here
        unordered_set<string> found;
        for (string word : dictionary)
        {
            if (exist(board, word))
            {
                found.insert(word);
            }
        }
        vector<string> res(found.begin(), found.end());
        sort(res.begin(), res.end());
        return res;
    }

    void findMaximumNumUtil(string &s, int k, string &maxNum, int idx = 0)
    {
        if (k == 0)
            return;
        int n = s.size();
        char maxDigit = s[idx];
        for (int i = idx + 1; i < n; i++)
        {
            if (s[i] > maxDigit)
                maxDigit = s[i];
        }
        if (maxDigit != s[idx])
            k--;
        for (int i = n - 1; i >= idx; i--)
        {
            if (s[i] == maxDigit)
            {
                if (i != idx)
                {
                    swap(s[idx], s[i]);
                    if (s.compare(maxNum) > 0)
                        maxNum = s;
                    findMaximumNumUtil(s, k, maxNum, idx + 1);
                    swap(s[idx], s[i]);
                }
                else
                {
                    findMaximumNumUtil(s, k, maxNum, idx + 1);
                }
            }
        }
    }
    string findMaximumNum(string &s, int k)
    {
        string maxNum = s;
        findMaximumNumUtil(s, k, maxNum, 0);
        return maxNum;
    }

    bool canPartition(vector<int> &arr, int k, vector<bool> &visited, int &target, int currSum, int index)
    {
        if (k == 1)
        {
            return true;
        }
        if (currSum == target)
        {
            return canPartition(arr, k - 1, visited, target, 0, 0);
        }
        for (int i = index; i < arr.size(); i++)
        {
            if (currSum + arr[i] <= target && !visited[i])
            {
                visited[i] = true;
                if (canPartition(arr, k, visited, target, currSum + arr[i], index + 1))
                {
                    return true;
                }
                visited[i] = false;
            }
        }
        return false;
    }
    bool isKPartitionPossible(vector<int> &arr, int k)
    {
        int totalSum = accumulate(arr.begin(), arr.end(), 0);
        if (totalSum % k != 0)
        {
            return false;
        }
        vector<bool> visited(arr.size(), false);
        int target = totalSum / k;
        sort(arr.begin(), arr.end());
        return canPartition(arr, k, visited, target, 0, 0);
    }

};

int main()
{
    Backtracking bt;
    vector<vector<int>> mat = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}};
    string s = "255678166";

    vector<vector<char>> board = {{'C'}, {'A'}, {'T'}};

    vector<string> dictionary;
    dictionary.push_back("CAP");
    dictionary.push_back("AND");
    dictionary.push_back("TIE");

    vector<int> input = {1, 2, 3};

    auto ans =
        bt.generateIp(s);
    // cout << ans;
    // for (auto a : ans)
    // {
    //     cout << a << " ";
    // }
    for (auto a : ans)
    {
        for (auto b : a)
        {
            cout << b;
        }
        cout <<endl;
    }
    // for (const auto &row : mat)
    // {
    //     for (int num : row)
    //     {
    //         cout << num << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}