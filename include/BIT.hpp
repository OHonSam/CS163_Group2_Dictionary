#pragma once

// BIT: Binary Indexed Tree - Fenwick Tree
// Careful: 1-indexed
class BIT
{
private:
    const int LOGN=20;

    int n;
    int *bit;

public:
    BIT(int n);
    ~BIT();

    int get(int i);
    void add(int i, int x);

    int lower_bound(int x);
};