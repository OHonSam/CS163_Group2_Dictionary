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
