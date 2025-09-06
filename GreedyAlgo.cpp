#include <bits/stdc++.h>
using namespace std;

class GreedyAlgo
{
private:
public:
    int minJumps(vector<int> &arr)
    {
        int n = arr.size();
        if (n <= 1)
            return 0;
        if (arr[0] == 0)
            return -1;

        int jumps = 0;
        int maxReach = arr[0];
        int steps = arr[0];

        for (int i = 1; i < n; i++)
        {
            if (i == n - 1)
                return jumps + 1;

            maxReach = max(maxReach, i + arr[i]);
            steps--;

            if (steps == 0)
            {
                jumps++;
                if (i >= maxReach)
                    return -1;
                steps = maxReach - i;
            }
        }
        return -1;
    }

    int minOperation(int n)
    {
        int ans = 0;
        while (n > 0)
        {
            if (n % 2 == 0)
            {
                n = n / 2;
            }
            else
            {
                n--;
            }
            ans++;
        }
        return ans;
    }

    long long int minValue(vector<int> &arr1, vector<int> &arr2)
    {
        sort(arr1.begin(), arr1.end());
        sort(arr2.begin(), arr2.end());

        long long int sum = 0;
        int n = arr2.size();
        for (int i = 0; i < arr1.size(); i++)
        {
            sum += (long long)arr1[i] * arr2[n - i - 1];
        }
        return sum;
    }

    string findLargest(int n, int s)
    {
        if (s == 0 && n == 1)
            return "0";
        if (s == 0 || s > 9 * n)
            return "-1";
        string ans = "";
        for (int i = 0; i < n; i++)
        {
            int digit = min(9, s);
            ans += to_string(digit);
            s -= digit;
        }
        return ans;
    }

    bool lemonadeChange(int N, vector<int> &bills)
    {
        int five = 0, ten = 0;
        for (int i = 0; i < N; i++)
        {
            if (bills[i] == 5)
            {
                five++;
            }
            else if (bills[i] == 10)
            {
                if (five == 0)
                    return false;
                five--;
                ten++;
            }
            else if (bills[i] == 20)
            {
                if (ten > 0 && five > 0)
                {
                    ten--;
                    five--;
                }
                else if (five >= 3)
                {
                    five -= 3;
                }
                else
                {
                    return false;
                }
            }
        }
        return true;
    }

    int maxMeetings(vector<int> &start, vector<int> &end)
    {
        vector<pair<int, int>> meetings;
        int count = 0;
        int n = start.size();
        for (int i = 0; i < n; i++)
        {
            meetings.push_back({end[i], start[i]});
        }

        sort(meetings.begin(), meetings.end());

        int lastEnd = -1;
        for (int i = 0; i < n; i++)
        {
            if (meetings[i].second > lastEnd)
            {
                count++;
                lastEnd = meetings[i].first;
            }
        }
        return count;
    }

    vector<int> maxMeetings2(vector<int> &start, vector<int> &end)
    {
        vector<pair<int, int>> meetings;
        vector<int> count;
        int n = start.size();
        for (int i = 0; i < n; i++)
        {
            meetings.push_back({end[i], start[i]});
        }

        sort(meetings.begin(), meetings.end());

        int lastEnd = -1;
        for (int i = 0; i < n; i++)
        {
            if (meetings[i].second > lastEnd)
            {
                count.push_back(i);
                lastEnd = meetings[i].first;
            }
        }
        return count;
    }

    int findPlatform(vector<int> &arr, vector<int> &dep)
    {
        // Your code here
        sort(arr.begin(), arr.end());
        sort(dep.begin(), dep.end());
        int n = arr.size();
        int i = 1, j = 0;
        int platNeed = 1, result = 1;
        while (i < n && j < n)
        {
            if (arr[i] <= dep[j])
            {
                platNeed++;
                i++;
            }
            else
            {
                platNeed--;
                j++;
            }
            if (platNeed > result)
            {
                result = platNeed;
            }
        }
        return result;
    }

    int getMinDiff(vector<int> &arr, int k)
    {
        if (arr.size() == 1)
            return 0;
        sort(arr.begin(), arr.end());
        int n = arr.size();
        int ans = arr[n - 1] - arr[0];

        int smallest = arr[0] + k;
        int largest = arr[n - 1] - k;

        for (int i = 1; i < n; i++)
        {
            if (arr[i] - k < 0)
                continue;
            int mi = min(smallest, arr[i] - k);
            int mx = max(largest, arr[i - 1] + k);
            ans = min(ans, mx - mi);
        }
        return ans;
    }

    int getMin(int n)
    {
        // code here
        vector<int> denom = {10, 5, 2, 1};
        int count = 0;
        for (auto coin : denom)
        {
            if (n >= coin)
            {
                count += n / coin;
                n = n % coin;
            }
        }
        return count;
    }

    vector<int> minPartition(int N)
    {
        // code here
        if (N <= 0)
        {
            return {-1};
        }
        vector<int> ans;
        vector<int> indianCurrency = {1, 2, 5, 10, 20, 50, 100, 200, 500, 2000};

        for (int i = indianCurrency.size() - 1; i >= 0; i--)
        {
            while (N >= indianCurrency[i])
            {
                ans.push_back(indianCurrency[i]);
                N -= indianCurrency[i];
            }
        }
        return ans;
    }

    vector<int> jobSequencing(vector<int> &deadline, vector<int> &profit)
    {
        int n = deadline.size();
        vector<pair<int, int>> jobs;
        for (int i = 0; i < n; i++)
        {
            jobs.push_back({profit[i], deadline[i]});
        }
        // Sort jobs by profit in descending order
        sort(jobs.rbegin(), jobs.rend());

        int maxDeadLine = 0;
        for (int i = 0; i < n; i++)
        {
            maxDeadLine = max(maxDeadLine, jobs[i].second);
        }

        vector<int> slot(maxDeadLine + 1, -1); // slot[i] = -1 means free
        int count = 0, sum = 0;
        for (int i = 0; i < n; i++)
        {
            // Find a free slot for this job (from its deadline to 1)
            for (int j = jobs[i].second; j > 0; j--)
            {
                if (slot[j] == -1)
                {
                    slot[j] = i;
                    count++;
                    sum += jobs[i].first;
                    break;
                }
            }
        }
        return {count, sum};
    }

    double fractionalKnapsack(vector<int> &val, vector<int> &wt, int capacity)
    {
        int n = val.size();
        vector<pair<double, int>> ratio_idx;
        for (int i = 0; i < n; i++)
        {
            ratio_idx.push_back({(double)val[i] / wt[i], i});
        }
        sort(ratio_idx.rbegin(), ratio_idx.rend());

        double ans = 0.0;
        int currWeight = 0;
        for (int i = 0; i < n; i++)
        {
            int idx = ratio_idx[i].second;
            if (currWeight + wt[idx] <= capacity)
            {
                currWeight += wt[idx];
                ans += val[idx];
            }
            else
            {
                int remain = capacity - currWeight;
                ans += (double)val[idx] * ((double)remain / wt[idx]);
                break;
            }
        }
        return round(ans * 1e6) / 1e6;
    }

    bool canReach(vector<int> &arr)
    {
        int maxJump = 0;
        int i = 0;
        int n = arr.size() - 1;
        while (i < n)
        {
            if (arr[i] == 0)
            {
                if (maxJump != 0)
                {
                    maxJump--;
                }
                else
                {
                    return false;
                }
            }
            maxJump = arr[i];
            i += maxJump;
        }

        return true;
    }

    vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
    {
        vector<vector<int>> ans;
        int n = intervals.size();
        int i = 0;
        // start
        while (i < n && intervals[i][1] < newInterval[0])
        {
            ans.push_back(intervals[i]);
            i++;
        }
        // middle
        while (i < n && intervals[i][0] <= newInterval[1] && intervals[i][1] >= newInterval[0])
        {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        ans.push_back(newInterval);

        // end
        while (i < n)
        {
            ans.push_back(intervals[i]);
            i++;
        }
        return ans;
    }

    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        if (intervals.empty())
            return {};
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> ans;
        ans.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++)
        {
            if (intervals[i][0] <= ans.back()[1])
            {
                ans.back()[1] = max(ans.back()[1], intervals[i][1]);
            }
            else
            {
                ans.push_back(intervals[i]);
            }
        }
        return ans;
    }

    int eraseOverlapIntervals(vector<vector<int>> &intervals)
    {
        if (intervals.empty())
            return 0;
        sort(intervals.begin(), intervals.end(), [](const vector<int> &a, const vector<int> &b)
             { return a[1] < b[1]; });
        int count = 0;
        int end = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++)
        {
            if (intervals[i][0] < end)
            {
                count++;
            }
            else
            {
                end = intervals[i][1];
            }
        }
        return count;
    }

    vector<int> partitionLabels(string s)
    {
        vector<int> ans;
        vector<int> lastIndex(26, 0);
        for (int i = 0; i < s.length(); i++)
        {
            lastIndex[s[i] - 'a'] = i;
        }
        int size = 0;
        int end = 0;
        for (int i = 0; i < s.length(); i++)
        {
            size += 1;
            end = max(end, lastIndex[s[i] - 'a']);
            if (i == end)
            {
                ans.push_back(size);
                size = 0;
            }
        }
        return ans;
    }

    int maxNumberOfFamilies(int n, vector<vector<int>> &reservedSeats)
    {
        unordered_map<int, unordered_set<int>> reserved;
        for (const auto &seat : reservedSeats)
        {
            reserved[seat[0]].insert(seat[1]);
        }

        int result = 0;
        for (int row = 1; row <= n; ++row)
        {
            // If the row has no reserved seats, it can fit 2 groups
            if (reserved.find(row) == reserved.end())
            {
                result += 2;
                continue;
            }
            auto &seats = reserved[row];
            bool left = true, middle = true, right = true;
            // Check left block (2-5)
            for (int i = 2; i <= 5; ++i)
                if (seats.count(i))
                    left = false;
            // Check right block (6-9)
            for (int i = 6; i <= 9; ++i)
                if (seats.count(i))
                    right = false;
            // Check middle block (4-7)
            for (int i = 4; i <= 7; ++i)
                if (seats.count(i))
                    middle = false;
            if (left)
                result++;
            if (right)
                result++;
            if (!left && !right && middle)
                result++;
        }
        return result;
    }

    int sumExceptFirstLast(vector<int> &arr)
    {
        // Your code here
        if (arr.size() < 2)
        {
            return 0;
        }
        int sum = 0;
        for (int i = 1; i < arr.size() - 1; i++)
        {
            sum += arr[i];
        }
        return sum;
    }

    int minAddToMakeValid(string s)
    {
        int openCount = 0;
        int closeCount = 0;
        for (auto c : s)
        {
            if (c == '(')
            {
                openCount++;
            }
            else
            {
                if (openCount != 0)
                {
                    openCount--;
                }
                else
                {
                    closeCount++;
                }
            }
        }
        return openCount + closeCount;
    }

    int minAddToMakeValid2(string s)
    {
        int openCount = 0;
        int closeCount = 0;
        for (auto c : s)
        {
            if (c == '(' || c == '[' || c == '{')
            {
                openCount++;
            }
            else
            {
                if (openCount != 0)
                {
                    openCount--;
                }
                else
                {
                    closeCount++;
                }
            }
        }
        return openCount + closeCount;
    }

    int minAddToMakeValid3(string s)
    {
        // using stack
        stack<char> st;
        for (auto c : s)
        {
            if (c == '(' || c == '[' || c == '{')
            {
                st.push(c);
            }
            else
            {
                if (st.empty())
                {
                    st.push(c);
                }
                if ((c == ')' && st.top() == '(') || (c == ']' && st.top() == '[') || (c == '}' && st.top() == '{'))
                {
                    st.pop();
                }
            }
        }

        return st.size();
    }

    long long solve(vector<int> &bt)
    {
        // code here
        int time = 0;
        int waitingTime = 0;
        sort(bt.begin(), bt.end());
        for (int i = 0; i < bt.size(); i++)
        {
            waitingTime += time;
            time += bt[i];
        }
        return waitingTime / bt.size();
    }
};

int main()
{
    GreedyAlgo gl;

    vector<vector<int>> input1 = {{1, 2}, {1, 3}, {1, 8}, {2, 6}, {3, 1}, {3, 10}};
    vector<int> input2 = {1, 2, 3, 4};
    string s = "()]";
    int n = 8;
    vector<int> start = {1, 5, 8, 10};
    vector<int> finish = {910, 1200, 1120, 1130, 1900, 2000};

    auto ans = gl.minPartition(3500);
    // cout << ans;

    for (auto it : ans)
    {
        cout << it << " ";
    }

    // for (auto it : ans)
    // {
    //     for (auto i : it)
    //     {
    //         cout << i << " ";
    //     }
    //     cout << " ";
    // }
    return 0;
}