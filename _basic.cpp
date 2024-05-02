#include"_basic.h"


QString N2S(int num)
{
    QString res = "";
    do
    {
        res.append((char)(num % 10 + '0'));
        num /= 10;
    } while (num);

    QString s2 = "";
    for (int i = res.length() - 1; i >= 0; i--)
    {
        s2.append(res[i]);
    }
    return s2;
}

int S2N(QString s)                                          //×¢Òâ¼ì´í
{
    long long res = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i].toLatin1() > '9' || s[i].toLatin1() < '0') {
            return -1;
        }
        res = res * 10 + ((s[i].toLatin1()) - '0');
    }
    if (res > ((1LL << 31) - 1) || s.length() > 10) {
        return -2;
    }
    return res;
}

int randint(int l, int r)
{
    return (rand() % (r - l + 1)) + l;
}

string stringFromSS(stringstream& ss)
{
    string s;
    string tmp;
    while (getline(ss, tmp))
    {
        s = s + "\n" + tmp;
    }
    return s;
}