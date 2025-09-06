#include <bits/stdc++.h>
using namespace std;

class Recurssion
{
public:
    void printMatrix(const vector<vector<int>> &matrix)
    {
        for (const auto &row : matrix)
        {
            for (int val : row)
            {
                cout << val << " ";
            }
            cout << endl;
        }
    }

    void printNos(int n)
    {
        if (n > 0)
        {
            printNos(n - 1);
            cout << n << " ";
        }
    }

    int factorial(int n)
    {
        if (n <= 1)
        {
            return 1;
        }
        return n * factorial(n - 1);
    }

    int nthFibonacci(int n)
    {
        if (n <= 1)
        {
            return n;
        }
        int last = nthFibonacci(n - 1);
        int slast = nthFibonacci(n - 2);
        return last + slast;
    }

    int reverseExponentiation(int n)
    {
        int a = n % 10; // get last digit
        int b = n / 10; // remove last digit from input and hold remaining

        cout << "a: " << a << "b: " << b;
        return 0;
    }

    void printPattern2(int n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                cout << "*";
            }
            cout << endl;
        }
    }

    void printPattern3(int n)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                cout << j;
            }
            cout << endl;
        }
    }

    void printPattern4(int n)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                cout << i;
            }
            cout << endl;
        }
    }

    void printPattern5(int n)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n - i + 1; j++)
            {
                cout << j;
            }
            cout << endl;
        }
    }

    void printPattern6(int n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int x = 0; x < n - i - 1; x++)
            {
                cout << " ";
            }
            for (int j = 0; j < 2 * i + 1; j++)
            {
                cout << "*";
            }
            cout << endl;
        }
    }

    void printPattern8(int n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int k = 0; k < i; k++)
            {
                cout << " ";
            }
            for (int j = 0; j < 2 * n - (2 * i + 1); j++)
            {
                cout << "*";
            }
            for (int x = 0; x < i; x++)
            {
                cout << " ";
            }
            cout << endl;
        }
    }

    void generatePattern(int n, int original, vector<int> &result, bool decrease)
    {
        result.push_back(n); // Add the current number to the result

        if (n == original && !decrease) // Base condition when pattern is complete
            return;

        if (decrease)
        {
            if (n - 5 > 0)
                generatePattern(n - 5, original, result, true); // Continue decreasing
            else
                generatePattern(n - 5, original, result, false); // Switch to increasing phase
        }
        else
        {
            generatePattern(n + 5, original, result, false); // Continue increasing
        }
    }

    vector<int> pattern(int n)
    {
        vector<int> result;
        generatePattern(n, n, result, true);
        return result;
    }

    vector<int> nthRowOfPascalTriangle(int n)
    {
        vector<int> res;
        int ans = 1;
        res.push_back(ans);
        for (int i = 1; i < n; i++)
        {
            ans = ans * (n - i);
            ans = ans / i;
            res.push_back(ans);
        }
        return res;
    }
};
int main()
{
    Recurssion r;
    auto ans = r.nthRowOfPascalTriangle(4);
    for (auto a : ans)
    {
        cout << a << " ";
    }
    return 0;
}