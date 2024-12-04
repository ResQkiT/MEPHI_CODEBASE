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
#include <memory>
#include "PriorityQueue.hpp"

template <class T>
class CachedDBAdapter : public DBAdapter<T> { 
private:
    struct CacheEntry {
        Query<T> query;
        std::vector<T> results;
        uint64_t access_count; 

        CacheEntry(Query<T> q, std::vector<T> r) 
            : query(std::move(q)), results(std::move(r)), access_count(1) {}

        bool operator<(const CacheEntry& other) const {
            return access_count < other.access_count;
        }
    };

    HashMap<Query<T>, std::shared_ptr<CacheEntry>, typename Query<T>::Hash> cache_map;
    PriorityQueue<std::shared_ptr<CacheEntry>> cache_queue; 
    size_t max_cache_size; 

public:
    CachedDBAdapter(const std::string& filename, size_t cache_size) 
        : DBAdapter<T>(filename), max_cache_size(cache_size) {}

    std::vector<T> find(const Query<T>& query) override {
        auto answer = cache_map.find(query);

        if (answer.has_value()) {
            std::cout << "Cache hit\n";
            answer.value().get().second->access_count++;
          
            return answer.value().get().second->results;
        }

        std::vector<T> results = DBAdapter<T>::find(query);

        auto entry = std::make_shared<CacheEntry>(query, results);

        cache_map[query] = entry;

        cache_queue.push(entry, 1);

        while (cache_queue.size() > max_cache_size) {
            std::shared_ptr<CacheEntry> least_used = cache_queue.pop_min();

            cache_map.erase(least_used->query);

        }

        return results;
    }
};
