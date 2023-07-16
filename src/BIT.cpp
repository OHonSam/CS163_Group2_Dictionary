#include "BIT.hpp"

BIT::BIT(int n)
{
    this->n = n;
    bit = new int[n + 1];
    for (int i = 0; i <= n; i++)
        bit[i] = 0;
}

BIT::~BIT()
{
    delete[] bit;
}

void BIT::clear()
{
    for (int i = 0; i <= n; i++)
        bit[i] = 0;
}

int BIT::get(int i)
{
    int sum = 0;
    while (i > 0)
    {
        sum += bit[i];
        i -= i & -i;
    }
    return sum;
}

void BIT::add(int i, int x)
{
    while (i <= n)
    {
        bit[i] += x;
        i += i & -i;
    }
}

int BIT::lower_bound(int x)
{
    int sum = 0, pos = 0;
    for (int i = LOGN; i >= 0; i--)
    {
        if (pos + (1 << i) < n && sum + bit[pos + (1 << i)] < x)
        {
            sum += bit[pos + (1 << i)];
            pos += (1 << i);
        }
    }
    return pos + 1;
}
