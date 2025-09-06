#include <bits/stdc++.h>
using namespace std;

class MathProblem
{
public:
    int getLastDigit(string a, string b)
    {
        // Get the last digit of 'a'
        int lastDigitA = a[a.length() - 1] - '0';

        // If exponent is "0", return 1 (anything^0 = 1)
        if (b == "0")
            return 1;

        // Compute b % 4 (to find the cycle position)
        int modCycle = 0;
        for (char ch : b)
        {
            modCycle = (modCycle * 10 + (ch - '0')) % 4;
        }

        // If modCycle is 0, we use 4 instead (because cycle repeats every 4)
        if (modCycle == 0)
            modCycle = 4;

        // Compute last digit of (lastDigitA ^ modCycle) using pow()
        int result = pow(lastDigitA, modCycle);
        return result % 10;
    }
    
    int countDigitInNumber(int n)
    {
        int count = 0;
        int temp = n;

        while (temp > 0)
        {
            int digit = temp % 10;
            if (digit != 0 && n % digit == 0)
            {
                count++;
            }
            temp /= 10;
        }
        return count;
    }

    int reverseNumber(int n)
    {
        int result = 0;
        bool leadingZero = true;
        while (n > 0)
        {
            int digit = n % 10;
            if (digit == 0 && leadingZero)
            {
                n /= 10;
                continue;
            }
            leadingZero = false;
            result = result * 10 + digit;
            n /= 10;
        }
        return result;
    }

    int findPower(int n)
    {
        int digit = 0;
        int reverseDigit = 0;
        int temp = n;
        int result = 0;
        while (temp > 0)
        {
            digit = temp % 10;
            reverseDigit = reverseDigit * 10 + digit;
            temp /= 10;
        }
        result = pow(n, reverseDigit);
        return result;
    }

    int findGCD(int a, int b)
    {
        int rem = 1;
        int divisor = 0;
        int divident = 0;

        if (a > b)
        {
            divident = a;
            divisor = b;
        }
        else
        {
            divident = b;
            divisor = a;
        }
        while (rem != 0)
        {
            rem = divident % divisor;
            if (rem != 0)
            {
                divident = divisor;
                divisor = rem;
            }
        }
        return divisor;
    }

    int printDevisors(int n)
    {
        int temp = 1;
        int digit = 0;
        int result = 0;
        while (temp <= n)
        {
            if (n % temp == 0)
            {
                result = result * 10 + temp;
            }
            temp = temp + 1;
        }
        return result;
    }

    bool primeNumber(int n)
    {
        if (n == 1)
        {
            return false;
        }
        for (int i = 2; i <= n; i++)
        {
            if (n % i == 0)
            {
                if (i != n)
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool armstrongNumber(int n)
    {
        int temp = n;
        int digit = 0;
        int result = 0;
        while (temp > 0)
        {
            digit = temp % 10;
            result += pow(digit, 3);
            temp /= 10;
        }
        if (result == n)
        {
            return true;
        }
        return false;
    }

    bool isPalindrome(int n)
    {
        int temp = n;
        int digit = 0;
        int reverseNumber = 0;
        while (temp > 0)
        {
            digit = temp % 10;
            reverseNumber = reverseNumber * 10 + digit;
            temp /= 10;
        }
        if (reverseNumber == n)
        {
            return true;
        }
        return false;
    }

    int floorSqrt(int n)
    {
        int low = 1;
        int high = n;
        int mid = 0;
        int value = 0;
        while (low <= high)
        {
            mid = (low + high) / 2;
            value = (mid * mid);
            if (value <= n)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return high;
    }

    bool isPerfectNumber(int n)
    {
        if (n <= 1)
            return false; // Perfect numbers are greater than 1

        int sum = 1; // Start with 1 as it's always a divisor

        // Find divisors up to sqrt(n)
        for (int i = 2; i * i <= n; i++)
        {
            if (n % i == 0)
            {
                sum += i;
                if (i != n / i)
                { // Add the corresponding divisor
                    sum += n / i;
                }
            }
        }

        return sum == n; // C
    }

    int *printDivisors(int n, int &size)
    {
        // First count number of divisors to allocate array
        size = 0;
        for (int i = 1; i <= n; i++)
        {
            if (n % i == 0)
            {
                size++;
            }
        }

        // Allocate array dynamically
        int *divisors = new int[size];
        int index = 0;

        // Store divisors in array
        for (int i = 1; i <= n; i++)
        {
            if (n % i == 0)
            {
                divisors[index] = i;
                index++;
            }
        }

        return divisors;
    }

};

int main()
{
    MathProblem s;
    int size = 5;
    auto ans = s.isPerfectNumber(15);
    cout<<ans;
    // for (auto a : ans)
    // {
    //     cout << a << " ";
    // }
    return 0;
}
