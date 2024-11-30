#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <functional>
#include "Query.hpp"

template <typename T, typename = void>
class BDAadapter;

template <typename T>
class BDAadapter<T, std::enable_if_t<std::is_constructible_v<T, std::string>>> {
private:
    std::string m_filename;
    std::ifstream m_file;

public:
    BDAadapter(const std::string& filename) : m_filename(filename) {
        m_file.open(filename);
        if (!m_file.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
        }
    }

    ~BDAadapter() {
        if (m_file.is_open()) {
            m_file.close();
        }
    }

    BDAadapter(const BDAadapter&) = delete;
    BDAadapter& operator=(const BDAadapter&) = delete;

    void resetFile() {
        m_file.clear();
        m_file.seekg(0, std::ios::beg);
    }

    std::vector<T> readAll() {
        std::vector<T> records;
        std::string line;

        if (!m_file.is_open()) {
            throw std::runtime_error("File is not open.");
        }

        while (std::getline(m_file, line)) {
            records.push_back(T(line));
        }

        resetFile(); 

        return records;
    }

    T readNext() {
        std::string line;
        if (!std::getline(m_file, line)) {
            throw std::runtime_error("No more records to read.");
        }
        return T(line);
    }


    std::vector<T> find(const Query<T>& query) {
        if (!m_file.is_open()) {
            throw std::runtime_error("File is not open.");
        }

        std::vector<T> matching_records;
        std::string line;
        m_file.clear();
        m_file.seekg(0, std::ios::beg);

        try {
            while (std::getline(m_file, line)) {
                T record(line);
                if (query.evaluate(record)) {
                    matching_records.push_back(record);
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception occurred during find: " << e.what() << std::endl;
            throw;
        }

        resetFile();

        return matching_records;
    }
};
