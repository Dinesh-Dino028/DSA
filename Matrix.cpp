#include <bits/stdc++.h>
using namespace std;

class Matrix
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target) // binary search
    {
        int n = matrix.size();
        int m = matrix[0].size();
        int low = 0, high = n * m - 1;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            int row = mid / m;
            int col = mid % m;
            if (matrix[row][col] == target)
            {
                return true;
            }
            else if (matrix[row][col] < target)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return false;
    }

    void rotateby90AntiClock(vector<vector<int>> &mat)
    {
        int n = mat.size();

        // Step 1: Transpose the matrix
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                swap(mat[i][j], mat[j][i]);
            }
        }

        // Step 2: Reverse each column
        for (int col = 0; col < n; col++)
        {
            int top = 0, bottom = n - 1;
            while (top < bottom)
            {
                swap(mat[top][col], mat[bottom][col]);
                top++;
                bottom--;
            }
        }
    }

    void rotateby90Clock(vector<vector<int>> &mat)
    {
        int n = mat.size();
        int m = mat[0].size();

        // tranpose
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                swap(mat[i][j], mat[j][i]);
            }
        }

        // reverse
        for (int i = 0; i < n; i++)
        {
            reverse(mat[i].begin(), mat[i].end());
        }
    }

    vector<vector<int>> rotateMatrix(int k, vector<vector<int>> mat)
    {
        int n = mat.size();
        int m = mat[0].size();
        k = k % 4; // Since rotating 4 times results in the original matrix

        for (int r = 0; r < k; r++)
        {
            vector<vector<int>> temp(m, vector<int>(n));
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    temp[m - j - 1][i] = mat[i][j];
                }
            }
            mat = temp;
            swap(n, m); // Swap dimensions for the next rotation
        }

        return mat;
    }

    int minRow(vector<vector<int>> &mat)
    {
        int minRowIndex = 0;
        int count = INT_MAX;
        int n = mat.size();
        int m = mat[0].size();
        for (int i = 0; i < n; i++)
        {
            int currCount = 0;
            for (int j = 0; j < m; j++)
            {
                if (mat[i][j] == 1)
                {
                    currCount++;
                }
            }
            if (currCount < count)
            {
                count = currCount;
                minRowIndex = i;
            }
        }
        return minRowIndex + 1;
    }

    vector<vector<int>> setZeroes(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<int> row(n, 0);
        vector<int> col(m, 0);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (matrix[i][j] == 0)
                {
                    row[i] = 1;
                    col[j] = 1;
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (row[i] || col[j])
                {
                    matrix[i][j] = 0;
                }
            }
        }

        return matrix;
    }

};
int main()
{
    Matrix m;
    vector<vector<int>> mat = {{1,1,1},{1,0,1},{1,1,1}};
    //auto ans = 
    //cout<<ans;
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