#pragma once
#include <iostream>
#include <unordered_map>
#include <memory>
#include <queue>
#include <optional>
#include "DBAdapter.hpp" 
#include "Query.hpp"
#include "HashMap.hpp"
#include <utility>

template <class T>
class CachedDBAdapter : public DBAdapter<T> { 
private:
    HashMap<Query<T>, std::vector<T>, typename Query<T>::Hash> cache; 
    std::queue<Query<T>> cached_queue; 
    size_t max_cache_size; 

public:
    CachedDBAdapter(const std::string& filename, size_t cache_size) 
        : DBAdapter<T>(filename), max_cache_size(cache_size) {}

    std::vector<T> find(const Query<T>& query) override {
        std::cout <<"new method\n";
        auto answer = cache.find(query); 
        if (answer.has_value()) {
            std::cout << "in cache!"<< '\n';
            return answer.value().get().second;
        }

        std::vector<T> results = DBAdapter<T>::find(query);
        cache.add_or_edit(query, std::move(results));
        cached_queue.push(query);


        if (cached_queue.size() > max_cache_size) {
            Query<T> oldest_query = cached_queue.front();
            cached_queue.pop();
            cache.erase(oldest_query); 
        }

        return results;
    }
};
