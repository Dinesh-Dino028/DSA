#include <bits/stdc++.h>
using namespace std;

class Sorting
{
public:
    // Sorting Algorithm

    //    Bubble Sort

    void bubbleSort(int arr[], int n)
    {
        for (int i = n - 1; i > 0; i--)
        {
            int didSwap = 0;
            for (int j = 0; j <= i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    int temp = arr[j + 1];
                    arr[j + 1] = arr[j];
                    arr[j] = temp;
                    didSwap = 1;
                }
            }
            if (didSwap == 0)
            {
                break; // Break the loop if array is already sorted.
            }
        }
    }

    void bubbleSort2(vector<int> &arr)
    {
        int n = arr.size();
        for (int i = n - 1; i > 0; i--)
        {
            int didSwap = 0;
            for (int j = 0; j <= i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    int temp = arr[j + 1];
                    arr[j + 1] = arr[j];
                    arr[j] = temp;
                    didSwap = 1;
                }
            }
            if (didSwap == 0)
            {
                break;
            }
        }
    }

    // Selection Sort

    void selectionSort(int arr[], int n)
    {
        for (int i = 0; i <= n - 2; i++)
        {
            int min = i;
            for (int j = i; j <= n - 1; j++)
            {
                if (arr[j] < arr[min])
                {
                    min = j;
                }
            }
            int temp = arr[min];
            arr[min] = arr[i];
            arr[i] = temp;
        }
    }

    void selectionSort2(vector<int> &arr)
    {
        int n = arr.size();
        for (int i = 0; i <= n - 2; i++)
        {
            int mini = i;
            for (int j = i; j <= n - 1; j++)
            {
                if (arr[j] < arr[mini])
                {
                    mini = j;
                }
            }
            int temp = arr[mini];
            arr[mini] = arr[i];
            arr[i] = temp;
        }
    }

    // INSERTIONS SORT

    void insertionSort(int arr[], int n)
    {
        for (int i = 0; i <= n - 1; i++)
        {
            int j = i;
            while (j > 0 && arr[j - 1] > arr[j])
            {
                int temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
                j--;
            }
        }
    }

    void insertionSort2(vector<int> &arr)
    {
        int n = arr.size();
        for (int i = 0; i <= n - 1; i++)
        {
            int j = i;
            while (j > 0 && arr[j - 1] > arr[j])
            {
                int temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
                j--;
            }
        }
    }

    // MERGE SORT

    void merge(vector<int> &arr, int l, int m, int r)
    {
        vector<int> temp;
        int left = l;
        int right = m + 1;
        while (left <= m && right <= r)
        {
            if (arr[left] <= arr[right])
            {
                temp.push_back(arr[left]);
                left++;
            }
            else
            {
                temp.push_back(arr[right]);
                right++;
            }
        }
        while (left <= m)
        {
            temp.push_back(arr[left]);
            left++;
        }
        while (right <= r)
        {
            temp.push_back(arr[right]);
            right++;
        }
        for (int i = l; i <= r; i++)
        {
            arr[i] = temp[i - l];
        }
    }
    void mergeSort(vector<int> &arr, int l, int r)
    {
        if (l == r)
        {
            return;
        }
        int mid = (l + r) / 2;
        mergeSort(arr, l, mid);
        mergeSort(arr, mid + 1, r);
        merge(arr, l, mid, r);
    }

    int partition(vector<int> &arr, int low, int high)
    {
        int pivot = arr[low];
        int i = low;
        int j = high;
        while (i < j)
        {
            while (arr[i] <= pivot && i <= high - 1)
            {
                i++;
            }
            while (arr[j] > pivot && j >= low + 1)
            {
                j--;
            }
            if (i < j)
            {
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[low], arr[j]);
        return j;
    }
    void quickSort(vector<int> &arr, int low, int high)
    {
        if (low < high)
        {
            int partIndex = partition(arr, low, high);
            quickSort(arr, low, partIndex - 1);
            quickSort(arr, partIndex + 1, high);
        }
    }
};
int main()
{
    Sorting s;
    vector<int> arr = {4, 6, 2, 5, 7, 9, 1, 3};
    s.quickSort(arr, 0, 7);
    for (auto a : arr)
    {
        cout << a << " ";
    }
    return 0;
}