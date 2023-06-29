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

void BIT::add(int i, int x)
{
    while (i <= n)
    {
        bit[i] += x;
        i += i & -i;
    }
}
