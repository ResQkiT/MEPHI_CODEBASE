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
    // Путь к каталогу static
    std::filesystem::path static_dir = "static";

    // Создаем каталог static, если он не существует
    if (!std::filesystem::exists(static_dir)) {
        std::filesystem::create_directory(static_dir);
    }

    // Создаем путь к файлу в каталоге static
    std::filesystem::path filepath = static_dir / filename;

    // Открываем файл для записи
    std::ofstream ofs;
    ofs.open(filepath);
    if (!ofs.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath.string());
    }

    // Генерируем случайные числа и записываем их в файл
    for (int i = 0; i < size; i++)
    {
        ofs << generate_random_number(min, max) << " ";
    }

    // Закрываем файл
    ofs.close();
}