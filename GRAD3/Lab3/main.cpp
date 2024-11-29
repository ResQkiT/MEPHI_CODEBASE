#include <iostream>
#include <string>
#include <cstring>
#include "HashMap.hpp"
#include "test.h"
#include <cassert>
#include <unordered_map>

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "-t") == 0)
    {
        run_test();
        return 0;
    }
    
}