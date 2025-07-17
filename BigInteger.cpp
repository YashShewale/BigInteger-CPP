#pragma once
#ifndef BIGINTERGER_H
#define BIGINTERGER_H

#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <math.h>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <map>

using namespace std;
typedef long long int ll;

class BigInteger
{
private:
    int compare(string a, string b) //return 1 if a is greater or return 0 if b is greater
    {
        if (a == b)
            return -1;
        int lena = a.length(), lenb = b.length();
        if (lena > lenb)
            return 1;
        else if (lenb > lena)
            return 0;
        else
        {
            for (int i = 0; i < lena; i++)
            {
                if (a[i] > b[i])
                    return 1;
                else if (a[i] < b[i])
                    return 0;
            }
        }
        return 1;
    }

    string removeTrailingZeros(string a)
    {
        int i = a.size() - 1;
        while (a[i] == '0' && i > 0)
        {
            a.pop_back();
            i--;
        }
        return a;
    }

    string multiplyHelper(string one, string two)
    {
        string temp = "";
        reverse(one.begin(), one.end());
        reverse(two.begin(), two.end());
        ll maxL = max(one.size(), two.size());
        ll carry = 0, i, csum;
        for (i = 0; i < maxL; i++)
        {
            csum = (i < one.size() ? one[i] - '0' : 0) + (i < two.size() ? two[i] - '0' : 0) + carry;
            carry = csum / 10;
            temp.push_back((csum % 10) + '0');
        }

        while (carry)
        {
            temp.push_back((carry % 10) + '0');
            carry /= 10;
        }
        reverse(temp.begin(), temp.end());
        return temp;
    }

    string divide_Table_Calculator(string a, string b)
    {
        string multiplicand, multiplier;
        if (a.size() > b.size())
            multiplicand = a, multiplier = b;
        else
            multiplicand = b, multiplier = a;

        reverse(multiplicand.begin(), multiplicand.end());
        reverse(multiplier.begin(), multiplier.end());

        string ans = "0";

        for (int i = 0; i < multiplier.size(); i++)
        {
            ll carry = 0;
            ll mul = multiplier[i] - '0';
            string temp = "";

            for (int j = 0; j < multiplicand.size(); j++)
            {
                ll cmul = (multiplicand[j] - '0') * mul + carry;
                temp.push_back((cmul % 10) + '0');
                carry = cmul / 10;
            }
            while (carry)
            {
                temp.push_back((carry % 10) + '0');
                carry /= 10;
            }
            reverse(temp.begin(), temp.end());
            ll zeroadd = i;
            while (zeroadd--)
                temp.push_back('0');

            ans = multiplyHelper(ans, temp);
        }
        reverse(ans.begin(), ans.end());
        ans = removeTrailingZeros(ans);
        reverse(ans.begin(), ans.end());
        return ans;
    }

    string divide_intermediate_subtractor(string a, string b)
    {
        string temp = "";
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        for (int i = 0; i < a.size(); i++)
        {
            ll csub = a[i] - '0' - (i < b.size() ? b[i] - '0' : 0);
            if (csub >= 0)
            {
                temp.push_back(csub + '0');
            }
            else
            {
                csub = 10 + (a[i] - '0') - (i < b.size() ? b[i] - '0' : 0);
                a[i + 1] = (a[i + 1] - '0' - 1) + '0';
                temp.push_back(csub + '0');
            }
        }
        temp = removeTrailingZeros(temp);
        reverse(temp.begin(), temp.end());
        return temp;
    }

    // Karatsuba helper
    string karatsuba(const string &x, const string &y)
    {
        int n = max(x.size(), y.size());
        if (n == 1)
        {
            int mul = (x[0] - '0') * (y[0] - '0');
            return to_string(mul);
        }
        int m = n / 2;

        string x1 = x.substr(0, x.size() - m);
        string x0 = x.substr(x.size() - m);
        string y1 = y.substr(0, y.size() - m);
        string y0 = y.substr(y.size() - m);

        while (x1.size() < x.size() - m) x1 = "0" + x1;
        while (x0.size() < m) x0 = "0" + x0;
        while (y1.size() < y.size() - m) y1 = "0" + y1;
        while (y0.size() < m) y0 = "0" + y0;

        string z2 = karatsuba(x1, y1);
        string z0 = karatsuba(x0, y0);

        BigInteger bx1(x1), bx0(x0), by1(y1), by0(y0);
        string sumx = bx1.add(x0);
        string sumy = by1.add(y0);
        string z1 = karatsuba(sumx, sumy);

        BigInteger bz1(z1), bz2(z2), bz0(z0);
        z1 = bz1.sub(bz2.a);
        z1 = BigInteger(z1).sub(z0);

        for (int i = 0; i < 2 * m; ++i) z2 += "0";
        for (int i = 0; i < m; ++i) z1 += "0";

        BigInteger result(z2);
        result.a = result.add(z1);
        result.a = result.add(z0);
        result.a = removeTrailingZeros(result.a);
        return result.a;
    }

public:
    string a;

    BigInteger()
    {
        a = "";
    }

    BigInteger(string t)
    {
        a = t;
    }

    void print()
    {
        cout << a;
    }

    string add(string b)
    {
        string temp = "";
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        ll maxL = max(a.size(), b.size());
        ll carry = 0, i, csum;
        for (i = 0; i < maxL; i++)
        {
            csum = (i < a.size() ? a[i] - '0' : 0) + (i < b.size() ? b[i] - '0' : 0) + carry;
            carry = csum / 10;
            temp.push_back((csum % 10) + '0');
        }
        while (carry)
        {
            temp.push_back((carry % 10) + '0');
            carry /= 10;
        }
        reverse(a.begin(), a.end());
        temp = removeTrailingZeros(temp);
        reverse(temp.begin(), temp.end());
        return temp;
    }

    string abs()
    {
        string temp = a;
        if (temp[0] == '-')
        {
            reverse(temp.begin(), temp.end());
            a.pop_back();
            reverse(temp.begin(), temp.end());
        }
        return temp;
    }

    bool compare(string b) //return 1 if a is greater or return 0 if b is greater
    {
        int lena = a.length(), lenb = b.length();
        if (lena > lenb)
            return 1;
        else if (lenb > lena)
            return 0;
        else
        {
            for (int i = 0; i < lena; i++)
            {
                if (a[i] > b[i])
                    return 1;
                else if (a[i] < b[i])
                    return 0;
            }
        }
        return 1;
    }

    string sub(string b)
    {
        string temp = "";
        bool x = compare(b);
        string sub1, sub2;
        if (x)
        {
            sub1 = a;
            sub2 = b;
        }
        else
        {
            sub1 = b;
            sub2 = a;
        }
        reverse(sub1.begin(), sub1.end());
        reverse(sub2.begin(), sub2.end());
        int min_len = sub2.length();
        int max_len = sub1.length();
        for (int i = min_len; i < max_len; i++)
            sub2.push_back(0 + '0');
        for (int i = 0; i < max_len; i++)
        {
            if (sub1[i] < sub2[i])
            {
                int a = sub1[i] - '0';
                a = 10 + a;
                int b = sub2[i] - '0';
                a = a - b;
                temp.push_back(a + '0');
                sub1[i + 1]--;
            }
            else
            {
                temp.push_back(((sub1[i] - '0') - (sub2[i] - '0')) + '0');
            }
        }
        for (int i = max_len - 1; i > 0; i--)
        {
            if (temp[i] == 0 + '0')
                temp.pop_back();
            else
                break;
        }
        if (!x)
            temp.push_back('-');
        temp = removeTrailingZeros(temp);
        reverse(temp.begin(), temp.end());
        return temp;
    }

    string multiply(string b)
    {
        bool neg = ((a[0] == '-' && b[0] == '-') || (a[0] != '-' && b[0] != '-')) ? 0 : 1;
        string multiplicand, multiplier;
        if (a.size() > b.size())
            multiplicand = a, multiplier = b;
        else
            multiplicand = b, multiplier = a;

        reverse(multiplicand.begin(), multiplicand.end());
        reverse(multiplier.begin(), multiplier.end());

        if (multiplicand[multiplicand.size() - 1] == '-')
            multiplicand.pop_back();
        if (multiplier[multiplier.size() - 1] == '-')
            multiplier.pop_back();

        string ans = "0";

        for (int i = 0; i < multiplier.size(); i++)
        {
            ll carry = 0;
            ll mul = multiplier[i] - '0';
            string temp = "";

            for (int j = 0; j < multiplicand.size(); j++)
            {
                ll cmul = (multiplicand[j] - '0') * mul + carry;
                temp.push_back((cmul % 10) + '0');
                carry = cmul / 10;
            }
            while (carry)
            {
                temp.push_back((carry % 10) + '0');
                carry /= 10;
            }
            reverse(temp.begin(), temp.end());
            ll zeroadd = i;
            while (zeroadd--)
                temp.push_back('0');

            ans = multiplyHelper(ans, temp);
        }
        reverse(ans.begin(), ans.end());
        ans = removeTrailingZeros(ans);
        if (neg) ans.push_back('-');
        reverse(ans.begin(), ans.end());
        return ans;
    }

    string divide(string b)
    {
        if (b == "1")
            return a;
        if (a == "0" || a == "00")
            return "0";
        if (b == "0" || b == "00")
            return "DIVIDE OVERFLOW";
        int cmp = compare(a, b);
        if (cmp == -1) // a & b equal
            return "1";
        else if (cmp == 0) //b > a
            return "0";
        else
        {
            vector<string> table;
            table.clear();
            table.push_back("-1");
            for (int i = 1; i <= 9; i++)
                table.push_back(divide_Table_Calculator(b, to_string(i)));

            for (int i = 1; i <= 9; i++)
                cout << i << " " << table[i] << endl;

            string q, r, temp;
            int i = 0;

            while (1)
            {
                bool t = 0;
                if (compare(temp, b) == 0 && i < a.size())
                {
                    t = 1;
                    temp.push_back(a[i]);
                    i++;
                    if (compare(temp, b) == 0)
                        q.push_back('0');
                }
                else
                {
                    bool inloop = 0;
                    reverse(temp.begin(), temp.end());
                    temp = removeTrailingZeros(temp);
                    reverse(temp.begin(), temp.end());

                    cout << "ready temp " << temp << endl;
                    int j = table.size() - 1;

                    while (compare(temp, table[j]) == 0 && temp != "0" && j >= 1) { inloop = 1, --j; }

                    temp = divide_intermediate_subtractor(temp, table[j]);
                    cout << "Minus " << temp << endl;

                    if (temp.size() == 1 && temp[0] == '0')
                        temp.clear();
                    if (inloop && j != 0)
                        q.push_back(j + '0');
                    else
                    {
                        q.push_back('0');
                    }
                    t = 0;
                }
                if (compare(temp, b) == 0 && i == a.size())
                {
                    break;
                }
            }
            reverse(q.begin(), q.end());
            q = removeTrailingZeros(q);
            reverse(q.begin(), q.end());
            return q;
        }
    }

    string valueOf(ll n)
    {
        string temp = to_string(n);
        return temp;
    }

    // Karatsuba multiplication (public)
    string karatsubaMultiply(string b)
    {
        string x = a, y = b;
        int len = max(x.size(), y.size());
        while (x.size() < len) x = "0" + x;
        while (y.size() < len) y = "0" + y;
        string res = karatsuba(x, y);
        res = removeTrailingZeros(res);
        return res;
    }

    // Fast exponentiation (binary exponentiation)
    string fastExponentiation(string b)
    {
        BigInteger base(a);
        BigInteger exp(b);
        BigInteger result("1");
        string zero = "0";
        string one = "1";
        while (exp.a != zero)
        {
            if ((exp.a.back() - '0') % 2 == 1)
            {
                result.a = result.multiply(base.a);
            }
            base.a = base.multiply(base.a);
            // Divide exp by 2
            string newExp = "";
            int carry = 0;
            for (char ch : exp.a)
            {
                int num = carry * 10 + (ch - '0');
                newExp += to_string(num / 2);
                carry = num % 2;
            }
            newExp = removeTrailingZeros(newExp);
            exp.a = newExp;
        }
        return result.a;
    }
};

#endif // BIGINTERGER_H