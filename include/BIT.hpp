#pragma once

// BIT: Binary Indexed Tree - Fenwick Tree
// Careful: 1-indexed
class BIT
{
private:
    int n;
    int *bit;

public:
    BIT(int n);
    ~BIT();

    int get(int i);
    void add(int i, int x);
};