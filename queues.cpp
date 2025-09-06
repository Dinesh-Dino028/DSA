#include <iostream>
#include <queue>
#include <stack>
#include <bits/stdc++.h>
using namespace std;

class Queue
{
private:
    int n;
    int *arr;
    int head;
    int tail;
    int count;

public:
    Queue(int size = 5)
    {
        n = size;
        arr = new int[n];
        head = 0;
        tail = 0;
        count = 0;
    }
    ~Queue()
    {
        delete[] arr;
    }
    void push(int val)
    {
        if (count == n)
        {
            cout << "Queue is full\n";
            return;
        }
        arr[tail] = val;
        tail = (tail + 1) % n;
        count++;
    }
    int pop()
    {
        if (count == 0)
        {
            cout << "Queue is empty\n";
            return -1;
        }
        int val = arr[head];
        head = (head + 1) % n;
        count--;
        return val;
    }

    // Queue Operations
    queue<int> reverseQueue(queue<int> &q)
    {
        stack<int> s;
        while (!q.empty())
        {
            s.push(q.front());
            q.pop();
        }

        while (!s.empty())
        {
            q.push(s.top());
            s.pop();
        }
        return q;
    }

    int startStation(vector<int> &gas, vector<int> &cost)
    {
        int n = gas.size();
        queue<int> q;

        for (int i = 0; i < n; i++)
        {
            q.push(i); // Try each station
        }

        while (!q.empty())
        {
            int start = q.front();
            q.pop();
            int tank = 0;
            int count = 0;
            int idx = start;

            while (count < n)
            {
                tank += gas[idx] - cost[idx];
                if (tank < 0)
                {
                    break; // Failed, try next start
                }
                idx = (idx + 1) % n;
                count++;
            }

            if (count == n)
            {
                return start; // Found valid start
            }
        }
        return -1;

        // optimal aproach
        /*         int totalTank = 0;
                int gain = 0;
                int currTank = 0;
                int startIndex = 0;
                int n = gas.size();

                for (int i = 0; i < n; ++i)
                {
                    gain = gas[i] - cost[i];
                    totalTank += gain;
                    currTank += gain;
                    if (gain < 0)
                    {
                        currTank = 0;
                        startIndex = i + 1;
                    }
                }

                return totalTank >= 0 ? startIndex : -1; */
    }

    string FirstNonRepeating(string &s)
    {
        vector<int> freq(26, 0);
        queue<char> q;
        string result;

        for (char ch : s)
        {
            freq[ch - 'a']++;

            // push to queue if first time seen
            q.push(ch);

            // Remove all repeated characters from front
            while (!q.empty() && freq[q.front() - 'a'] > 1)
            {
                q.pop();
            }

            if (!q.empty())
            {
                result += q.front();
            }
            else
            {
                result += '#';
            }
        }

        return result;
    }

    queue<int> reverseFirstK(queue<int> q, int k)
    {
        stack<int> s;
        int temp = k;
        if (k <= 0)
        {
            return q;
        }
        for (int i = 0; i < k; i++)
        {
            s.push(q.front());
            q.pop();
        }
        while (!s.empty())
        {
            q.push(s.top());
            s.pop();
        }
        int rem = q.size() - k;
        while (rem--)
        {
            q.push(q.front());
            q.pop();
        }
        return q;
    }

    int minCost(vector<int> &arr)
    {
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (int a : arr)
        {
            minHeap.push(a);
        }
        int totalCost = 0;
        while (minHeap.size() > 1)
        {
            int first = minHeap.top();
            minHeap.pop();
            int second = minHeap.top();
            minHeap.pop();

            int cost = first + second;
            totalCost += cost;
            minHeap.push(cost);
        }
        return totalCost;
    }

    void nearlySorted(vector<int> &arr, int k)
    {
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (int a : arr)
        {
            minHeap.push(a);
        }
        for (int i = 0; i <= arr.size() - 1; i++)
        {
            arr[i] = minHeap.top();
            minHeap.pop();
        }
    }
};

// Interview Question
class LRUCache
{
    int capacity;                                          // capacity
    list<pair<int, int>> cache;                            // {key, value}
    unordered_map<int, list<pair<int, int>>::iterator> mp; // key -> iterator
public:
    LRUCache(int cap)
    {
        capacity = cap;
    }

    int get(int key)
    {
        if (mp.find(key) == mp.end())
        {
            return -1; // not found
        }
        // Move this key-value to the front (most recently used)
        auto it = mp[key];
        int value = it->second;
        cache.erase(it);
        cache.push_front({key, value});
        mp[key] = cache.begin();
        return value;
    }

    void put(int key, int value)
    {
        if (mp.find(key) != mp.end())
        {
            // Key already exists -> update value & move to front
            auto it = mp[key];
            cache.erase(it);
        }
        else if ((int)cache.size() == capacity)
        {
            // Remove least recently used (last element)
            auto last = cache.back();
            mp.erase(last.first);
            cache.pop_back();
        }
        // Insert new key-value at front
        cache.push_front({key, value});
        mp[key] = cache.begin();
    }
};

int main()
{
    Queue q;
    // q.push(5);
    // q.push(10);
    // q.push(15);

    // cout << q.pop() << endl; // 5
    // cout << q.pop() << endl; // 10
    // cout << q.pop() << endl; // 15
    // cout << q.pop() << endl; // Queue is empty, -1
    queue<int> q1;
    q1.push(4);
    q1.push(3);
    q1.push(1);
    q1.push(10);
    q1.push(2);
    q1.push(6);

    vector<int> gas;
    gas.push_back(4);
    gas.push_back(5);
    gas.push_back(7);
    gas.push_back(4);
    vector<int> cost;
    cost.push_back(6);
    cost.push_back(6);
    cost.push_back(3);
    cost.push_back(5);
    q.startStation(gas, cost);

    // string s = "aabc";
    vector<int> arr = {6, 5, 3, 2, 8, 10, 9};

    //    q1 = q.reverseFirstK(q1,3);
    //     while(!q1.empty()){
    //         cout<<q1.front()<<" ";
    //         q1.pop();
    //     }
    // q.startStation(arr,0);
    for (int a : arr)
    {
        cout << a << " ";
    }
}