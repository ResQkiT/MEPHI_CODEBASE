#include "DataGenerator.h"
#include <iostream>
#include <random>
#include <fstream>
#include <filesystem>

DataGenerator::DataGenerator() : gen(rd()) {}
int DataGenerator::generate_random_number(int min, int max)
{
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void DataGenerator::generate_random_array(int *arr, int size, int min, int max)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = generate_random_number(min, max);
    }
}

void DataGenerator::generate_random_data_file(const std::string &filename, int size, int min, int max)
{
    std::filesystem::path static_dir = "static";

 
    if (!std::filesystem::exists(static_dir)) {
        std::filesystem::create_directory(static_dir);
    }

    std::filesystem::path filepath = static_dir / filename;

    std::ofstream ofs;
    ofs.open(filepath);
    if (!ofs.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath.string());
    }

    for (int i = 0; i < size; i++)
    {
        ofs << generate_random_number(min, max) << " ";
    }

    ofs.close();
}