#include "BIT.hpp"

BIT::BIT(int n)
{
    this->n = n;
    this->bit = new int[n + 1];
    for (int i = 0; i <= n; i++)
        this->bit[i] = 0;
}