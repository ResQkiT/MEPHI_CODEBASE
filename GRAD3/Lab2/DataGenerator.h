#pragma once

#include <string>
#include <random>
#include <fstream>

class DataGenerator
{
private:
    std::random_device rd;
    std::mt19937 gen;

public:
    DataGenerator();
    int generate_random_number(int min, int max);
    void generate_random_array(int *arr, int size, int min, int max);
    void generate_random_data_file(const std::string &filename, int size, int min, int max);
};