#include <bits/stdc++.h>
#include <vector>
using namespace std;

class SlidingWindow
{
private:
public:
    int maximumSumSubarray(vector<int> &arr, int k)
    {
        int n = arr.size();
        if (k > n || k <= 0)
            return 0;
        int windowSum = 0, maxSum = 0;
        // Compute sum of first window of size k
        for (int i = 0; i < k; i++)
        {
            windowSum += arr[i];
        }
        maxSum = windowSum;
        // Slide the window
        for (int i = k; i < n; i++)
        {
            windowSum += arr[i] - arr[i - k];
            maxSum = max(maxSum, windowSum);
        }
        return maxSum;
    }

    vector<int> countDistinct(vector<int> &arr, int k)
    {
        vector<int> ans;
        unordered_map<int, int> um;
        int n = arr.size();

        if (k > n || k <= 0)
            return ans;

        for (int i = 0; i < k; i++)
        {
            um[arr[i]]++;
        }
        ans.push_back(um.size());

        for (int i = k; i < n; i++)
        {
            um[arr[i - k]]--;
            if (um[arr[i - k]] == 0)
            {
                um.erase(arr[i - k]);
            }
            um[arr[i]]++;
            ans.push_back(um.size());
        }

        return ans;
    }

    vector<int> firstNegInt(vector<int> &arr, int k)
    {
        int n = arr.size();
        queue<int> q;
        vector<int> res;

        int end = 0, start = 0;
        while (end < n)
        {
            if (arr[end] < 0)
            {
                q.push(end);
            }

            if (end - start + 1 == k)
            {
                if (!q.empty())
                {
                    res.push_back(arr[q.front()]);
                }
                else
                {
                    res.push_back(0);
                }

                if (!q.empty() && q.front() == start)
                {
                    q.pop();
                }
                start++;
            }
            end++;
        }
        return res;
    }

    vector<int> maxOfSubarrays(vector<int> &arr, int k)
    {
        deque<int> dq;
        vector<int> res;
        int n = arr.size();
        for (int i = 0; i < n; i++)
        {
            if (!dq.empty() && dq.front() == i - k)
            {
                dq.pop_front();
            }
            while (!dq.empty() && arr[dq.back()] < arr[i])
            {
                dq.pop_back();
            }
            dq.push_back(i);
            if (i >= k - 1)
            {
                res.push_back(arr[dq.front()]);
            }
        }
        return res;
    }

    int countOfSubstrings(string S, int K)
    {
        int distinct = 0;
        int count = 0;
        unordered_map<int, int> fr;

        for (int i = 0; i < K; i++)
        {
            if (fr[S[i]] == 0)
            {
                distinct++;
            }
            fr[S[i]]++;
        }

        if (distinct == K - 1)
        {
            count++;
        }

        for (int i = K; i < S.size(); i++)
        {
            // Remove
            char out = S[i - K];
            fr[out]--;
            if (fr[out] == 0)
            {
                distinct--;
            }

            // Add
            char in = S[i];
            if (fr[in] == 0)
            {
                distinct++;
            }
            fr[in]++;
            if (distinct == K - 1)
            {
                count++;
            }
        }

        return count;
    }

    //Variable Window
    vector<int> subarraySum(vector<int> &arr, int target)
    {
        int n = arr.size();
        int left = 0, right = 0, sum = 0;
        vector<int> res;

        while (right < n)
        {
            sum += arr[right];
            while (sum > target && left <= right)
            {
                sum -= arr[left];
                left++;
            }
            if (sum == target)
            {
                res.push_back(left + 1);
                res.push_back(right + 1);
                break;
            }
            right++;
        }
        if (res.empty())
        {
            res.push_back(-1);
        }
        return res;
    }

    int longestSubarray(vector<int> &arr, int k)
    {
        unordered_map<long long, int> prefixSumIndex;
        long long sum = 0;
        int maxLen = 0;

        for (int i = 0; i < arr.size(); i++)
        {
            sum += arr[i];

            if (sum == k)
                maxLen = i + 1;

            if (prefixSumIndex.find(sum - k) != prefixSumIndex.end())
            {
                maxLen = max(maxLen, i - prefixSumIndex[sum - k]);
            }

            // Only store the first occurrence to get the longest length
            if (prefixSumIndex.find(sum) == prefixSumIndex.end())
                prefixSumIndex[sum] = i;
        }

        return maxLen;
    }

    bool subArrayExists(vector<int> &arr)
    {
        unordered_set<int> prefixSums;
        int sum = 0;

        for (int num : arr)
        {
            sum += num;

            if (sum == 0 || prefixSums.find(sum) != prefixSums.end())
                return true;

            prefixSums.insert(sum);
        }

        return false;
    }

    int findSubString(string &str)
    {
        unordered_set<char> s;

        for (char c : str)
        {
            s.insert(c);
        }

        int i = 0;
        int j = 0;
        int ans = str.size();
        int n = s.size();
        unordered_map<char, int> m;
        while (i < str.size())
        {
            m[str[i]]++;

            if (m.size() == n)
            {
                while (m[str[j]] > 1)
                {
                    m[str[j]]--;
                    j++;
                }
                ans = min(ans, i - j + 1);
            }
            i++;
        }
        return ans;
    }

    int smallestSubstring(string S)
    {
        int i = 0;
        int j = 0;
        int ans = INT_MAX;
        int n = 3;
        unordered_map<char, int> m;
        while (i < S.size())
        {
            if (S[i] == '0' || S[i] == '1' || S[i] == '2')
            {
                m[S[i]]++;
            }
            if (m.size() == n)
            {
                while (m[S[j]] > 1)
                {
                    m[S[j]]--;
                    j++;
                }
                ans = min(ans, i - j + 1);
            }
            i++;
        }
        if (ans == INT_MAX)
            return -1;
        return ans;
    }

    string smallestWindow(string &s1, string &s2)
    {
        if (s2.size() > s1.size())
            return "";

        unordered_map<char, int> need, window;
        for (char c : s2)
            need[c]++;

        int have = 0, needCount = need.size();
        int left = 0, minLen = INT_MAX, minStart = 0;

        for (int right = 0; right < s1.size(); right++)
        {
            char c = s1[right];
            window[c]++;
            if (need.count(c) && window[c] == need[c])
            {
                have++;
            }

            while (have == needCount)
            {
                if (right - left + 1 < minLen)
                {
                    minLen = right - left + 1;
                    minStart = left;
                }
                char leftChar = s1[left];
                window[leftChar]--;
                if (need.count(leftChar) && window[leftChar] < need[leftChar])
                {
                    have--;
                }
                left++;
            }
        }

        if (minLen == INT_MAX)
            return "";
        return s1.substr(minStart, minLen);
    }

    int longestUniqueSubstring(string &s)
    {
        vector<int> mpp(256, -1);
        int left = 0, right = 0;
        int n = s.size();
        int len = 0;
        while (right < n)
        {
            if (mpp[s[right] != -1])
            {
                left = max(left, mpp[s[right]] + 1);
            }
            mpp[s[right]] = right;
            len = max(len, right - left + 1);
            right++;
        }
        return len;
    }

    int maxLen(vector<int> &arr)
    {
        unordered_map<int, int> prefixSumIndex;
        int maxLen = 0;
        int sum = 0;

        for (int i = 0; i < arr.size(); i++)
        {

            if (arr[i] == 0)
            {
                sum += -1;
            }
            else
            {
                sum += 1;
            }

            if (sum == 0)
            {
                maxLen = i + 1; // 0 to current index
            }

            if (prefixSumIndex.find(sum) != prefixSumIndex.end()) // I already seen the same sum
            {
                maxLen = max(maxLen, i - prefixSumIndex[sum]);
            }
            else
            {
                prefixSumIndex[sum] = i;
            }
        }

        return maxLen;
    }

    int search(string &pat, string &txt)
    {
        int n = txt.size();
        int p = pat.size();

        if (n < p)
        {
            return 0;
        }

        unordered_map<char, int> freqPat, freqWindow;
        for (char ch : pat)
        {
            freqPat[ch]++;
        }

        int count = 0;
        for (int i = 0; i <= n; i++)
        {
            freqWindow[txt[i]]++;

            if (i >= p)
            {
                char removeChar = txt[i - p];
                freqWindow[removeChar]--;
                if (freqWindow[removeChar] == 0)
                {
                    freqWindow.erase(removeChar);
                }
            }

            // if match
            if (i >= p - 1 && freqWindow == freqPat)
            {
                count++;
            }
        }
        return count;
    }

    int longestOnes(vector<int> &nums, int k)
    {
        int n = nums.size();
        int left = 0, right = 0, zeroCount = 0, maxLen = 0;

        while (right < n)
        {
            if (nums[right] == 0)
            {
                zeroCount++;
            }

            while (zeroCount > k)
            {
                if (nums[left] == 0)
                {
                    zeroCount--;
                }
                left++;
            }

            maxLen = max(maxLen, right - left + 1);
            right++;
        }
        return maxLen;
    }

    int totalFruit(vector<int> &fruits)
    {
        unordered_map<int, int> basket;
        int left = 0, maxFruits = 0;
        for (int right = 0; right < fruits.size(); right++)
        {
            basket[fruits[right]]++;

            while (basket.size() > 2)
            {
                basket[fruits[left]]--;
                if (basket[fruits[left]] == 0)
                {
                    basket.erase(fruits[left]);
                }
                left++;
            }

            maxFruits = max(maxFruits, right - left + 1);
            right++;
        }

        return maxFruits;
    }

    int numberOfSubarrays(vector<int> &nums, int k)
    {
        int n = nums.size();
        int left = 0, right = 0, odds = 0, count = 0, prefix = 0;

        while (right < n)
        {
            if (nums[right] % 2 != 0)
            {
                odds++;
                prefix = 0;
            }

            while (odds == k)
            {
                if (nums[left] % 2 != 0)
                {
                    odds--;
                }
                prefix++;
                left++;
            }

            count += prefix;
            right++;
        }
        return count;
    }

    int characterReplacement(string s, int k)
    {
        int maxLen = 0;
        int maxFreq = 0;
        vector<int> freq(26, 0); // Frequency of each character
        int left = 0;

        for (int right = 0; right < s.length(); right++)
        {
            freq[s[right] - 'A']++;
            maxFreq = max(maxFreq, freq[s[right] - 'A']);

            // Window size = right - left + 1
            // If more than k changes are needed, shrink from left
            if ((right - left + 1) - maxFreq > k)
            {
                freq[s[left] - 'A']--;
                left++;
            }

            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }

    string minWindow(string s, string t)
    {
        if (s.size() < t.size())
            return "";
        unordered_map<char, int> need, window;
        for (char c : t)
            need[c]++;
        int have = 0, needCount = need.size();
        int left = 0, minLen = INT_MAX, minStart = 0;
        for (int right = 0; right < s.size(); right++)
        {
            char c = s[right];
            window[c]++;
            if (need.count(c) && window[c] == need[c])
            {
                have++;
            }
            while (have == needCount)
            {
                if (right - left + 1 < minLen)
                {
                    minLen = right - left + 1;
                    minStart = left;
                }
                char leftChar = s[left];
                window[leftChar]--;
                if (need.count(leftChar) && window[leftChar] < need[leftChar])
                {
                    have--;
                }
                left++;
            }
        }
        if (minLen == INT_MAX)
            return "";
        return s.substr(minStart, minLen);
    }

    int atMostKDistinct(vector<int> &nums, int k)
    {
        int n = nums.size();
        unordered_map<int, int> freq;
        int left = 0, count = 0;
        for (int right = 0; right < n; right++)
        {
            freq[nums[right]]++;
            while (freq.size() > k)
            {
                freq[nums[left]]--;
                if (freq[nums[left]] == 0)
                {
                    freq.erase(nums[left]);
                }
                left++;
            }
            count += right - left + 1;
        }
        return count;
    }
    int subarraysWithKDistinct(vector<int> &nums, int k)
    {
        return atMostKDistinct(nums, k) - atMostKDistinct(nums, k - 1);
    }
};

int main()
{
    SlidingWindow sw;
    vector<int> arr = {1,2,1,2,3};
    // arr.push_back(1);
    // arr.push_back(2);
    // arr.push_back(3);
    // arr.push_back(1);
    // arr.push_back(4);
    // arr.push_back(5);
    // arr.push_back(2);
    // arr.push_back(3);
    // arr.push_back(6);

    string s = "geeksforgeeks";
    string s2 = "ABC";

    auto ans = sw.subarraysWithKDistinct(arr, 2);
    cout << ans;
    // for (int a : ans)
    // {
    //     cout << a << " ";
    // }

    return 0;
}
