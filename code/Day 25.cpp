#include <bits/stdc++.h>

using namespace std;

unordered_map<char, int> toDec = {{'0', 0},
                                  {'1', 1},
                                  {'2', 2},
                                  {'=', -2},
                                  {'-', -1}};

string toSnafu = "012=-";

long long convertToDecimal(string & s)
{
    int n = s.length();
    long long fp = 1LL;
    long long ans = 0LL;
    for (int i = 0; i < n; ++i)
    {
        ans += fp * toDec[s[n - 1 - i]];
        fp *= 5;
    }
    return ans;
}

string convertToElf(long long n)
{
    string output{};
    output.reserve(20);
    int carryOver = 0;
    int digit;
    while (n > 0)
    {
        digit = n % 5;
        output.push_back(toSnafu[digit]);
        carryOver = (digit > 2 ? 1 : 0);
        n /= 5;
        n += carryOver;
    }
    reverse(output.begin(), output.end());
    return output;
}

int main()
{
    long long ans = 0LL;
    long long curr;
    string s;
    while (getline(cin, s))
    {
        curr = convertToDecimal(s);
        ans += curr;
    }
    cout << convertToElf(ans) << endl;
    return 0;
}
