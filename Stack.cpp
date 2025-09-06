#include <bits/stdc++.h>
#include <stack>
using namespace std;

class Stacks
{
private:
    int top = -1;
    int arr[5];

public:
    void push(int val)
    {
        arr[++top] = val;
    }
    int pop()
    {
        if (top < 0)
        {
            return top;
        }
        int val = arr[top--];
        return val;
    }
    int topVal()
    {
        return arr[top];
    }
    bool isEmpty()
    {
        return top == -1 ? true : false;
    }
};

class StackOperation
{
private:
    stack<char> st;

public:
    bool isBalanced(string &s)
    {
        for (char ch : s)
        {
            if (ch == '[' || ch == '{' || ch == '(')
            {
                st.push(ch);
            }
            else if (ch == ']' || ch == '}' || ch == ')')
            {
                if (st.empty())
                {
                    return false;
                }
                char c = st.top();
                st.pop();
                if ((ch == ']' && c != '[') ||
                    (ch == '}' && c != '{') ||
                    (ch == ')' && c != '('))
                {
                    return false;
                }
            }
        }
        return st.empty();
    }

    vector<int> nextLargerElement(vector<int> &arr)
    {
        vector<int> res(arr.size());
        stack<int> s;
        for (int i = arr.size() - 1; i >= 0; i--)
        {
            while (!s.empty() && s.top() <= arr[i])
            {
                s.pop();
            }
            if (!s.empty())
            {
                res[i] = s.top();
            }
            else
            {
                res[i] = -1;
            }
            s.push(arr[i]);
        }
        return res;
    }
    vector<int> nextGreaterElements(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> res(n, -1);
        stack<int> s;
        for (int i = 2 * n - 1; i >= 0; i--)
        {
            while (!s.empty() && s.top() <= nums[i % n])
            {
                s.pop();
            }
            if (i < n)
            {
                if (!s.empty())
                {
                    res[i] = s.top();
                }
            }
            s.push(nums[i % n]);
        }
        return res;
    }

    vector<int> help_classmate(vector<int> arr, int n)
    {
        vector<int> res(n);
        stack<int> s;
        for (int i = n - 1; i >= 0; i--)
        {
            while (!s.empty() && s.top() >= arr[i])
            {
                s.pop();
            }
            if (!s.empty())
            {
                res[i] = s.top();
            }
            else
            {
                res[i] = -1;
            }
            s.push(arr[i]);
        }
        return res;
    }

    vector<int> nextSmallerElement(vector<int> &arr, int n)
    {
        vector<int> result(n);
        stack<int> st;

        for (int i = n - 1; i >= 0; i--)
        {
            // Remove elements from stack that are not smaller
            while (!st.empty() && st.top() >= arr[i])
            {
                st.pop();
            }

            if (!st.empty())
            {
                result[i] = st.top();
            }
            else
            {
                result[i] = 1;
            }
            st.push(arr[i]);
        }

        return result;
    }

    vector<int> calculateSpan(vector<int> &arr)
    {
        int n = arr.size();
        vector<int> result(n);
        stack<int> st;
        for (int i = 0; i <= n - 1; i++)
        {
            // Remove elements from stack that are not smaller
            while (!st.empty() && arr[st.top()] <= arr[i])
            {
                st.pop();
            }

            // If stack is empty, no smaller element to the right
            result[i] = st.empty() ? (i + 1) : (i - st.top());

            // Push current element for next iteration
            st.push(i);
        }

        return result;
    }

    int maxWater(vector<int> &arr)
    {
        int i = 0;
        int j = arr.size() - 1;
        int left_max = 0;
        int right_max = 0;
        int res = 0;
        while (i < j)
        {
            if (arr[i] < arr[j])
            {
                if (arr[i] >= left_max)
                    left_max = arr[i];
                else
                    res += left_max - arr[i];
                i++;
            }
            else
            {
                if (arr[j] >= right_max)
                    right_max = arr[j];
                else
                    res += right_max - arr[j];
                j--;
            }
        }
        return res;
    }

    int largestRectangleArea(vector<int>& heights) {
    stack<int> st;
    int n = heights.size();
    int maxArea = 0;
    int i = 0;

    while (i < n) {
        // Push if stack is empty or current bar >= bar at top index
        if (st.empty() || heights[st.top()] <= heights[i]) {
            st.push(i++);
        } else {
            int top = st.top();
            st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            maxArea = max(maxArea, heights[top] * width);
        }
    }

    // Clear remaining bars
    while (!st.empty()) {
        int top = st.top();
        st.pop();
        int width = st.empty() ? i : i - st.top() - 1;
        maxArea = max(maxArea, heights[top] * width);
    }

    return maxArea;
}

    string infixToPostfix(string &s)
    {
        stack<char> st;
        string res;
        unordered_map<char, int> prec = {
            {'^', 3},
            {'/', 2},
            {'*', 2},
            {'+', 1},
            {'-', 1}};

        for (char c : s)
        {
            if (isalnum(c))
            {
                res += c;
            }
            else if (c == '(')
            {
                st.push(c);
            }
            else if (c == ')')
            {
                while (!st.empty() && st.top() != '(')
                {
                    res += st.top();
                    st.pop();
                }
                if (!st.empty())
                {
                    st.pop();
                }
            }
            else
            {
                // All operators are left-associative, pop operators of equal or higher precedence
                while (!st.empty() && st.top() != '(' &&
                       (prec[c] <= prec[st.top()]))
                {
                    res += st.top();
                    st.pop();
                }
                st.push(c);
            }
        }
        while (!st.empty())
        {
            res += st.top();
            st.pop();
        }
        return res;
    }

    int evaluate(vector<string> &arr)
    {
        stack<int> st;
        for (string &token : arr)
        {
            if (token == "+" || token == "-" || token == "*" || token == "/")
            {
                int a = st.top();
                st.pop();
                int b = st.top();
                st.pop();
                if (token == "+")
                {
                    st.push(b + a);
                }
                else if (token == "-")
                {
                    st.push(b - a);
                }
                else if (token == "*")
                {
                    st.push(b * a);
                }
                else
                {
                    st.push(b / a);
                }
            }
            else
            {
                st.push(stoi(token));
            }
        }
        return st.top();
    }

    string preToPost(string pre_exp)
    {
        stack<string> st;
        // Traverse from right to left
        for (int i = pre_exp.size() - 1; i >= 0; i--)
        {
            char c = pre_exp[i];
            if (isalnum(c))
            {
                st.push(string(1, c));
            }
            else
            {
                if (st.size() < 2)
                    return ""; // invalid expression
                string op1 = st.top();
                st.pop();
                string op2 = st.top();
                st.pop();
                string temp = op1 + op2 + c;
                st.push(temp);
            }
        }
        return st.empty() ? "" : st.top();
    }

    int evaluateArithmeticExpression(string &expression)
    {
        stack<int> nums;
        stack<char> ops;
        int n = expression.size();
        auto precedence = [](char op)
        {
            if (op == '+' || op == '-')
                return 1;
            if (op == '*' || op == '/')
                return 2;
            return 0;
        };
        auto apply = [](int a, int b, char op)
        {
            if (op == '+')
                return a + b;
            if (op == '-')
                return a - b;
            if (op == '*')
                return a * b;
            if (op == '/')
                return a / b;
            return 0;
        };
        for (int i = 0; i < n; ++i)
        {
            if (isspace(expression[i]))
                continue;
            if (isdigit(expression[i]))
            {
                int val = 0;
                while (i < n && isdigit(expression[i]))
                {
                    val = val * 10 + (expression[i] - '0');
                    ++i;
                }
                nums.push(val);
                --i;
            }
            else if (expression[i] == '(')
            {
                ops.push('(');
            }
            else if (expression[i] == ')')
            {
                while (!ops.empty() && ops.top() != '(')
                {
                    int b = nums.top();
                    nums.pop();
                    int a = nums.top();
                    nums.pop();
                    char op = ops.top();
                    ops.pop();
                    nums.push(apply(a, b, op));
                }
                if (!ops.empty())
                    ops.pop();
            }
            else if (expression[i] == '+' || expression[i] == '-' ||
                     expression[i] == '*' || expression[i] == '/')
            {
                while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i]))
                {
                    int b = nums.top();
                    nums.pop();
                    int a = nums.top();
                    nums.pop();
                    char op = ops.top();
                    ops.pop();
                    nums.push(apply(a, b, op));
                }
                ops.push(expression[i]);
            }
        }
        while (!ops.empty())
        {
            int b = nums.top();
            nums.pop();
            int a = nums.top();
            nums.pop();
            char op = ops.top();
            ops.pop();
            nums.push(apply(a, b, op));
        }
        return nums.empty() ? 0 : nums.top();
    }

    void stackInsertAtBottom(stack<int> &st, int x)
    {
        if (st.empty())
        {
            st.push(x);
            return;
        }

        int num = st.top();
        st.pop();
        stackInsertAtBottom(st, x); // backtracking
        st.push(num);
    }
    stack<int> insertAtBottom(stack<int> st, int x)
    {
        stackInsertAtBottom(st, x);
        return st;
    }

    void stackReverse(stack<int> &St)
    {
        if (St.empty())
        {
            return;
        }
        int num = St.top();
        St.pop();
        stackReverse(St);
        stackInsertAtBottom(St, num);
    }
    void Reverse(stack<int> &St)
    {
        stackReverse(St);
    }

    void sortedStack(stack<int> &s, int num)
    {
        if (s.empty() || num > s.top())
        {
            s.push(num);
            return;
        }
        int temp = s.top();
        s.pop();
        this->sortedStack(s, num);
        s.push(temp);
    }
    void sortStack(stack<int> &s)
    {
        if (s.empty())
        {
            return;
        }
        int num = s.top();
        s.pop();
        sortStack(s);
        sortedStack(s, num);
    }
    void SortedStack(stack<int> &s)
    {
        sortStack(s);
    }

    string Reduced_String(int k, string s)
    {
        stack<pair<char, int>> st;
        string res = "";
        if (k == 1)
        {
            return "";
        }
        for (int i = 0; i <= s.size() - 1; i++)
        {
            if (st.empty())
            {
                st.push({s[i], 1});
            }
            else if (!st.empty() && st.top().first == s[i])
            {
                st.push({s[i], st.top().second + 1});
                if (st.top().second == k)
                {
                    int temp = k;
                    while (temp--)
                    {
                        st.pop();
                    }
                }
            }
            else
            {
                st.push({s[i], 1});
            }
        }
        while (!st.empty())
        {
            res += st.top().first;
            st.pop();
        }
        reverse(res.begin(), res.end());

        return res;
    }

    int countMinReversals(string s)
    {
        stack<char> st;
        int count = 0;
        if (s.size() % 2 == 1)
        {
            return -1;
        }
        for (char c : s)
        {
            if (c == '{')
            {
                st.push(c);
            }
            else
            {
                if (st.empty())
                {
                    count++;
                    st.push('{');
                }
                else
                {
                    st.pop();
                }
            }
        }
        count = count + st.size() / 2;
        return count;
    }
};

int main()
{
    Stacks st;
    // st.push(10);
    // st.push(20);
    // st.push(30);
    // st.push(40);
    // cout<<st.topVal();
    // cout<<st.isEmpty();
    // cout << st.pop() << " ";
    // cout << st.pop() << " ";
    // cout << st.pop() << " ";
    // cout << st.pop() << " ";
    // cout << st.pop() << " ";
    // string s = "[()(){}]";
    // cout<<st.isBalanced(s);
    StackOperation so;
    vector<string> input = {"2", "3", "1", "*", "+", "9", "-"};
    // string s = "*-ABB";
    //  vector<int> res = so.calculateSpan(input);
    //  for (int r : res)
    //  {
    //      cout << r << " ";
    //  }
    stack<int> s;
    s.push(4);
    s.push(3);
    s.push(2);
    s.push(1);
    s.push(8);
    string str = "}{{}}{{{";
    vector<int> arr= {3, 0, 1, 0, 4, 0, 2};
    vector<string> str2= {"2", "3", "1", "*", "+", "9", "-"};
    auto ans = so.insertAtBottom(s, 2);
    
    //cout<<ans;
    // for(auto a: ans){
    //     cout<<a<<" ";
    // }

    // while (!s.empty())
    // {
    //     cout << s.top() << " ";
    //     s.pop();
    // }
};
