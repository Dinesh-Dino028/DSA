#include <bits/stdc++.h>
using namespace std;

class stringproblem
{
public:
    int myAtoi(char *s)
    {
        if (s == nullptr)
            return 0;

        int i = 0;

        // 1. Skip leading whitespaces
        while (s[i] == ' ')
        {
            i++;
        }

        // 2. Check for optional sign
        int sign = 1;
        if (s[i] == '+' || s[i] == '-')
        {
            if (s[i] == '-')
            {
                sign = -1;
            }
            i++;
        }

        // 3. Convert digits to number
        long result = 0;
        while (isdigit(s[i]))
        {
            int digit = s[i] - '0';
            result = result * 10 + digit;

            // 4. Handle overflow
            if (sign == 1 && result > INT_MAX)
                return INT_MAX;
            if (sign == -1 && -result < INT_MIN)
                return INT_MIN;

            i++;
        }

        return (int)(sign * result);
    }

    string countAndSay(int n)
    {
        if (n == 1)
        {
            return "1";
        }
        string prev = "1";
        for (int i = 2; i <= n; i++)
        {
            string curr = "";
            int count = 1;
            for (int j = 1; j < prev.size(); j++) // Fixed increment variable from i to j
            {
                if (prev[j] == prev[j - 1])
                {
                    count++;
                }
                else
                {
                    curr += to_string(count) + prev[j - 1];
                    count = 1;
                }
            }
            curr += to_string(count) + prev.back();
            prev = curr;
        }
        return prev;
    }

    int countMinReversals(string s)
    {
        int n = s.length();
        if (n % 2 != 0)
            return -1;
        stack<char> st;
        for (char c : s)
        {
            if (c == '}' && !st.empty())
            {
                if (st.top() == '{')
                {
                    st.pop();
                }
                else
                {
                    st.push(c);
                }
            }
            else
            {
                st.push(c);
            }
        }
        int len = st.size();
        int open = 0, close = 0;
        while (!st.empty())
        {
            if (st.top() == '{')
                open++;
            else
                close++;
            st.pop();
        }
        return (open + 1) / 2 + (close + 1) / 2;
    }

    // Important asked in curious interview
    vector<int> rabinKarpBruteForce(string &text, string &pattern)
    {
        int n = text.length();
        int m = pattern.length();
        vector<int> result;
        for (int i = 0; i <= n - m; i++)
        {
            int j = 0;
            while (j < m && text[i + j] == pattern[j])
            {
                j++;
            }
            if (j == m)
            {
                result.push_back(i);
            }
        }
        return result;
    }

    vector<int> rabinKarp(string &text, string &pattern)
    {
        int n = text.length();
        int m = pattern.length();
        vector<int> result;
        if (m > n)
        {
            return result;
        }
        const int d = 256; // input text ASCII value
        const int q = 101; // prime number to reduce the large hash value

        int h = 1;
        int p = 0; // hash value for pattern
        int t = 0; // hash value for text

        // calculate hash
        for (int i = 0; i < m - 1; i++)
        {
            h = (h * d) % q;
        }

        // calculate hash for pattern and text
        for (int i = 0; i < m; i++)
        {
            p = (d * p + pattern[i]) % q;
            t = (d * t + text[i]) % q;
        }

        // compare hash number match
        for (int i = 0; i <= n - m; i++)
        {
            if (p == t)
            {
                // check the character one by one if hashes match
                bool match = true;
                for (int j = 0; j < m; j++)
                {
                    if (text[i + j] != pattern[j])
                    {
                        match = false;
                        break;
                    }
                }
                if (match)
                {
                    result.push_back(i);
                }
            }

            // calculate hash for the next window of text
            if (i < n - m)
            {
                t = (d * (t - text[i] * h) + text[i + m]) % q;
                if (t < 0)
                {
                    t += q;
                }
            }
        }
        return result;
    }

    void badCHarHeuristic(string pattern, int badChar[])
    {

        int m = pattern.length();
        for (int i = 0; i < 256; i++)
        {
            badChar[i] = -1;
        }

        for (int i = 0; i < m; i++)
        {
            badChar[(int)pattern[i]] = i;
        }
    }
    // Boyer Moore Algo
    vector<int> patternSearch(string text, string pattern)
    {

        vector<int> result;
        int n = text.length();
        int m = pattern.length();

        if (m > n)
        {
            return {-1};
        }
        int badChar[256];
        badCHarHeuristic(pattern, badChar);
        int shift = 0;

        while (shift <= (n - m))
        {
            int j = m - 1;

            while (j >= 0 && text[shift + j] == pattern[j])
            {
                j--;
            }
            if (j < 0)
            {
                result.push_back(shift); // macth found

                shift += (shift + m < n) ? m - badChar[text[shift + m]] : 1;
            }
            else
            {
                shift += max(1, j - badChar[text[shift + j]]);
            }
        }
        if (result.empty())
        {
            return {-1};
        }
        return result;
    }

    // KMP algo
    int getLPSLength(string &s)
    {
        int n = s.length();
        vector<int> lps(n, 0);
        int i = 1;
        int len = 0;
        while (i < n)
        {
            if (s[i] == s[len])
            {
                len++;
                lps[i] = len;
                i++;
            }
            else
            {
                if (len != 0)
                {
                    len = lps[len - 1];
                }
                else
                {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return (lps[n - 1] == n) ? 0 : lps[n - 1];
    }

    string removeDuplicates(string s)
    {
        string result = "";
        stack<char> st;
        for (auto c : s)
        {
            if (!st.empty() && st.top() == c)
            {
                st.pop();
            }
            else
            {
                st.push(c);
            }
        }

        while (!st.empty())
        {
            result = st.top() + result;
            st.pop();
        }
        return result;
    }

    vector<int> stringCount1(string s)
    {
        vector<int> result;
        int n = s.length();
        int hash[26] = {0}; // use 26 alphapet size
        for (auto c : s)
        {
            hash[c - 'a'] += 1;
        }

        for (auto c : s)
        {
            result.push_back(hash[c - 'a']);
        }
        return result;
    }

    vector<int> stringCount2(string s)
    {
        vector<int> result;
        int n = s.length();
        // int hash[26] = {0}; // use 26 alphapet size
        int hash[256] = {0}; // use 256 ASCII size
        for (auto c : s)
        {
            hash[c] += 1;
        }

        for (auto c : s)
        {
            result.push_back(hash[c]);
        }
        return result;
    }
    vector<int> stringCount3(string s)
    {
        vector<int> result;
        int n = s.length();
        map<char, int> mpp; // sorted order
        for (auto c : s)
        {
            mpp[c]++;
        }
        for (auto c : s)
        {
            result.push_back(mpp[c]);
        }
        return result;
    }

    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        vector<vector<string>> result;
        unordered_map<string, vector<string>> mpp;
        for (auto s : strs)
        {
            string key = s;
            sort(key.begin(), key.end());
            mpp[key].push_back(s);
        }

        for (auto pair : mpp)
        {
            result.push_back(pair.second);
        }
        return result;
    }

    string shortestPalindrome(string s)
    {
        string rev = s;
        reverse(rev.begin(), rev.end());

        string combined = s + "#" + rev;
        int n = combined.length();

        vector<int> lps(n, 0);

        for (int i = 1; i < n; i++)
        {
            int len = lps[i - 1];
            while (len > 0 && combined[i] != combined[len])
                len = lps[len - 1];
            if (combined[i] == combined[len])
                len++;
            lps[i] = len;
        }

        int toAddLen = s.length() - lps[n - 1];
        string toAdd = s.substr(lps[n - 1]);
        reverse(toAdd.begin(), toAdd.end());

        return toAdd + s;
    }

    int romanToDecimal(string &s)
    {
        unordered_map<char, int> mpp;
        mpp['I'] = 1;
        mpp['V'] = 5;
        mpp['X'] = 10;
        mpp['L'] = 50;
        mpp['C'] = 100;
        mpp['D'] = 500;
        mpp['M'] = 1000;

        int total = 0;
        int n = s.length();
        for (int i = 0; i < n; i++)
        {
            int curr = mpp[s[i]];
            int next = (i + 1 < n) ? mpp[s[i + 1]] : 0;

            if (curr < next)
            {
                total -= curr;
            }
            else
            {
                total += curr;
            }
        }
        return total;
    }
};

int main()
{
    stringproblem sp;
    char s[] = "-123";
    string str1 = "IX";
    string pattern = "XYZ";
    vector<string> str = {"eat", "tea", "tan", "ate", "nat", "bat"};
    auto ans = sp.romanToDecimal(str1);
    cout << ans;
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
