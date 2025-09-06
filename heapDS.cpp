#include <bits/stdc++.h>
using namespace std;

class minHeap
{
public:
    vector<int> heap; // array to store heap elements

    // Constructor
    minHeap() {}

    // Helper: Heapify down (after extract or delete)
    void heapifyDown(int i)
    {
        int n = heap.size();
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && heap[left] < heap[smallest])
            smallest = left;
        if (right < n && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != i)
        {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    // Helper: Heapify up (after insert)
    void heapifyUp(int i)
    {
        while (i > 0)
        {
            int parent = (i - 1) / 2;
            if (heap[parent] > heap[i])
            {
                swap(heap[parent], heap[i]);
                i = parent;
            }
            else
            {
                break;
            }
        }
    }

    // ✅ Remove and return min element
    int extractMinElement()
    {
        if (heap.empty())
            return -1; // safety check

        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty())
            heapifyDown(0);

        return minVal;
    }

    // ✅ Delete element at index 'ind'
    void deleteElement(int ind)
    {
        if (ind >= heap.size())
            return; // invalid index

        heap[ind] = INT_MIN; // make it very small
        heapifyUp(ind);      // move it to root
        extractMinElement(); // remove root
    }

    // ✅ Insert new value
    void insert(int val)
    {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }
};

class maxHeap
{
public:
    vector<int> heap; // store elements

    maxHeap() {}

    // Heapify down (after extract or delete)
    void heapifyDown(int i)
    {
        int n = heap.size();
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && heap[left] > heap[largest])
            largest = left;
        if (right < n && heap[right] > heap[largest])
            largest = right;

        if (largest != i)
        {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

    // Heapify up (after insert)
    void heapifyUp(int i)
    {
        while (i > 0)
        {
            int parent = (i - 1) / 2;
            if (heap[parent] < heap[i])
            { // parent should be larger
                swap(heap[parent], heap[i]);
                i = parent;
            }
            else
            {
                break;
            }
        }
    }

    // ✅ Remove and return max element
    int extractMaxElement()
    {
        if (heap.empty())
            return -1; // safety check

        int maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty())
            heapifyDown(0);

        return maxVal;
    }

    // ✅ Delete element at index 'ind'
    void deleteElement(int ind)
    {
        if (ind >= heap.size())
            return; // invalid index

        heap[ind] = INT_MAX; // make it very large
        heapifyUp(ind);      // move to root
        extractMaxElement(); // remove root
    }

    // ✅ Insert new value
    void insert(int val)
    {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }
};

class heapDS
{
public:
    // using max heap
    vector<int> kLargest(vector<int> &arr, int k)
    {
        priority_queue<int> maxHeap(arr.begin(), arr.end());

        vector<int> result;
        for (int i = 0; i < k && !maxHeap.empty(); i++)
        {
            result.push_back(maxHeap.top());
            maxHeap.pop();
        }
        return result;
    }
    // using min heap
    vector<int> kLargest2(vector<int> &arr, int k)
    {
        priority_queue<int, vector<int>, greater<int>> minHeap;

        for (auto a : arr)
        {
            minHeap.push(a);
            if (minHeap.size() > k)
            {
                minHeap.pop();
            }
        }

        vector<int> result;
        while (!minHeap.empty())
        {
            result.push_back(minHeap.top());
            minHeap.pop();
        }

        sort(result.begin(), result.end());
        return result;
    }

    vector<int> kSmallest(vector<int> &arr, int k)
    {
        priority_queue<int, vector<int>, greater<int>> minHeap(arr.begin(), arr.end());
        vector<int> result;
        for (int i = 0; i < k && !minHeap.empty(); i++)
        {
            result.push_back(minHeap.top());
            minHeap.pop();
        }
        return result;
    }

    vector<int> kSmallest2(vector<int> &arr, int k)
    {
        priority_queue<int> maxHeap;
        for (auto a : arr)
        {
            maxHeap.push(a);
            if (maxHeap.size() > k)
            {
                maxHeap.pop();
            }
        }
        vector<int> result;
        while (!maxHeap.empty())
        {
            result.push_back(maxHeap.top());
            maxHeap.pop();
        }
        sort(result.begin(), result.end()); // Sort result to get ascending order
        return result;
    }

    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> freq;
        for (auto n : nums)
        {
            freq[n]++;
        }
        priority_queue<pair<int, int>> maxHeap;

        for (auto f : freq)
        {
            maxHeap.push({f.second, f.first});
        }

        vector<int> result;
        for (int i = 0; i < k; i++)
        {
            result.push_back(maxHeap.top().second);
            maxHeap.pop();
        }
        return result;
    }

    vector<string> topKFrequentString(vector<string> &words, int k)
    {
        unordered_map<string, int> freq;
        for (auto w : words)
        {
            freq[w]++;
        }

        auto comp = [](const pair<int, string> &a, const pair<int, string> &b)
        {
            return a.first < b.first || (a.first == b.first && a.second > b.second);
        };

        priority_queue<pair<int, string>, vector<pair<int, string>>, decltype(comp)> maxHeap(comp);

        for (auto f : freq)
        {
            maxHeap.push({f.second, f.first});
        }

        vector<string> result;
        for (int i = 0; i < k && !maxHeap.empty(); i++)
        {
            result.push_back(maxHeap.top().second);
            maxHeap.pop();
        }
        return result;
    }

    string frequencySort(string s)
    {
        unordered_map<char, int> freq;
        for (auto c : s)
        {
            freq[c]++;
        }

        priority_queue<pair<int, char>> maxHeap;

        for (auto f : freq)
        {
            maxHeap.push({f.second, f.first});
        }

        string str = "";
        while (!maxHeap.empty())
        {
            int count = maxHeap.top().first;
            char c = maxHeap.top().second;
            while (count > 0)
            {
                str += c;
                count--;
            }
            maxHeap.pop();
        }

        return str;
    }

    vector<int> kthLargest(int k, int arr[], int n)
    {
        priority_queue<int, vector<int>, greater<int>> minHeap;
        vector<int> result;
        for (int i = 0; i < n; i++)
        {
            minHeap.push(arr[i]);

            if (minHeap.size() < k)
            {
                result.push_back(-1);
            }
            else
            {
                if (minHeap.size() > k)
                {
                    minHeap.pop();
                }
                result.push_back(minHeap.top());
            }
        }
        return result;
    }

    // Given a string s, rearrange characters so no adjacent chars are same
    // 1. Count frequency of each char in a hashmap
    // 2. Use max heap to store char frequencies (most frequent chars processed first)
    // 3. For each iteration:
    //    - Get most frequent char (curr) from heap
    //    - Add it to result if different from previous char
    //    - Decrement its frequency and store as prev
    //    - Add back prev char to heap if it has remaining frequency
    // 4. Check final string has no adjacent same chars
    string reorganizeString(string s)
    {
        unordered_map<char, int> freq;
        for (auto c : s)
        {
            freq[c]++;
        }
        priority_queue<pair<int, char>> maxHeap;

        for (auto f : freq)
        {
            maxHeap.push({f.second, f.first});
        }
        string result = "";
        pair<int, char> prev = {0, '#'};

        while (!maxHeap.empty())
        {
            auto curr = maxHeap.top();
            maxHeap.pop();

            result += curr.second;
            curr.first--;

            if (prev.first > 0)
            {
                maxHeap.push(prev);
            }

            prev = curr;
        }

        for (int i = 1; i < result.size(); i++)
        {
            if (result[i] == result[i - 1])
            {
                return "";
            }
        }
        return result;
    }
};

int main()
{
    heapDS h;
    minHeap minH;
    maxHeap maxH;

    // minH.insert(10);
    // minH.insert(5);
    // minH.insert(20);
    // minH.insert(3);

    // cout << "Extract Min: " << minH.extractMinElement() << endl; // 3

    // minH.deleteElement(1); // delete element at index 1

    // cout << "Extract Min after delete: " << minH.extractMinElement() << endl; // should give remaining min
    vector<int> arr = {1, 2, 3, 4, 5, 6};
    vector<string> str = {"i", "love", "leetcode", "i", "love", "coding"};
    string s = "Aabb";
    int ar[] = {1, 2, 3, 4, 5, 6};
    auto ans = h.kthLargest(4, ar, 6);
    // cout << ans;
    for (auto a : ans)
    {
        cout << a << " ";
    }
    return 0;
}
