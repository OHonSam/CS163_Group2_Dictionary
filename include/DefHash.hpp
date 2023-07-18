#ifndef DEFHASH_HPP
#define DEFHASH_HPP

// #include "Libraries.hpp"

#include<iostream>
#include<fstream>
#include<vector>
#include<utility>//to use pair
#include<string>
#include <sstream>
#include <time.h>
#include<cstring>

class DefHash {
private:
    std::vector<std::vector<std::string>> buckets;

    int hash(const std::string& word);
public:
    DefHash() {
        buckets.resize(500);
    }
};
#endif