#pragma once
#include "../../GRAD2/Lab2/DynamicArray.h"
#include "../../GRAD2/Lab2/LinkedList.h"
#include <iostream>
#include <vector>
#include <forward_list>
#include <utility>
#include <algorithm>
#include <functional>

template <class K, class V, class Hash = std::hash<K>>
class HashMap {
private:
    using value_type = std::pair<const K, V>;

    DynamicArray<LinkedList<value_type>> hash_table;    
    size_t non_empty_buckets_count;
    size_t total_elements;

    size_t next_prime(size_t n) {
        while (!is_prime(n)) {
            ++n;
        }
        return n;
    }

    bool is_prime(size_t n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (size_t i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    void rehash() {
        if (size() != get_bucket_count()) {
            return;
        }

        size_t new_size = next_prime(hash_table.get_size() * 2); 
        DynamicArray<LinkedList<value_type>> new_table(new_size);
        size_t new_non_empty = 0;
        size_t new_total = 0;

        for (size_t i = 0; i < hash_table.get_size(); ++i) {
            for (size_t j = 0; j < hash_table[i].get_size(); ++j) {
                auto& item = hash_table[i].get(j);
                size_t hash = Hash{}(item.first);
                size_t index = hash % new_size; 
                
                if (new_table[index].is_empty()) {
                    ++new_non_empty;
                }
                new_table[index].push_front(std::move(item));
                ++new_total;
            }
        }

        hash_table = std::move(new_table);
        non_empty_buckets_count = new_non_empty;
        total_elements = new_total;
    }


    V& insert_or_get(K&& key) {

        size_t hash = Hash{}(key);
        size_t index = get_index_from_hash(hash);

        for (auto& item : hash_table[index]) {
            if (item.first == key) {
                return item.second;
            }
        }

        if (bucket_size(hash_table[index]) == 0) {
            ++non_empty_buckets_count;
        }

        hash_table[index].push_front({std::move(key), V()});
        ++total_elements;

        rehash();
        index = get_index_from_hash(hash);
        return hash_table[index].front().second;
    }

    size_t bucket_size(LinkedList<value_type>& bucket) const {
        return std::distance(bucket.begin(), bucket.end());
    }

    size_t get_bucket_count() const {
        return hash_table.get_size();
    }

    size_t get_index_from_hash(size_t hash) const {
        return hash % get_bucket_count();
    }

public:
    HashMap() : hash_table(3), non_empty_buckets_count(0), total_elements(0){}

    HashMap(const HashMap& other) : hash_table(other.get_bucket_count()), non_empty_buckets_count(0), total_elements(0)
    {
        for (const auto& bucket : other.hash_table) {
            for (const auto& item : bucket) {
                size_t hash = Hash{}(item.first);
                size_t index = get_index_from_hash(hash);
                if (bucket_size(hash_table[index]) == 1) {
                    ++non_empty_buckets_count;
                }
                hash_table[index].push_back(item);
                ++total_elements;
            }
        }
        rehash();
    }

    HashMap(HashMap&& other) noexcept : hash_table(std::move(other.hash_table)), non_empty_buckets_count(other.non_empty_buckets_count), total_elements(other.total_elements){
        other.non_empty_buckets_count = 0;
        other.total_elements = 0;
    }

    HashMap& operator=(const HashMap& other) {
        if (this != &other) {
            HashMap temp(other);
            swap(temp);
        }
        return *this;
    }

    HashMap& operator=(HashMap&& other) noexcept {
        if (this != &other) {
            hash_table = std::move(other.hash_table);
            non_empty_buckets_count = other.non_empty_buckets_count;
            total_elements = other.total_elements;
            other.non_empty_buckets_count = 0;
            other.total_elements = 0;
        }
        return *this;
    }

    V& operator[](const K& key) {
        return insert_or_get(K(key));
    }

    V& operator[](K&& key) {
        return insert_or_get(std::move(key));  
    }

    ~HashMap() = default;

    void swap(HashMap& other) {
        std::swap(hash_table, other.hash_table);
        std::swap(non_empty_buckets_count, other.non_empty_buckets_count);
        std::swap(total_elements, other.total_elements);
    }

    std::optional<std::reference_wrapper<value_type>> find(const K& k) {
        size_t hash = Hash{}(k);
        size_t index = get_index_from_hash(hash);
        for (auto& item : hash_table[index]) {
            if (item.first == k) {
                return item;
            }
        }
        return std::nullopt;
    }

    void add_or_edit(const K& k, V&& v) {
        size_t hash = Hash{}(k);
        size_t index = get_index_from_hash(hash);
        for (auto& item : hash_table[index]) {
            if (item.first == k) {
                item.second = std::forward<V>(v);
                return;
            }
        }
        hash_table[index].push_front({k, std::forward<V>(v)});
        ++total_elements;
        if (bucket_size(hash_table[index]) == 1) {
            ++non_empty_buckets_count;
        }
        rehash();
    }

    void erase(const K& k) {
        size_t hash = Hash{}(k);
        size_t index = get_index_from_hash(hash);
        auto& bucket = hash_table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == k) {
                bucket.erase(std::distance(bucket.begin(), it));
                --total_elements;
                if (bucket.is_empty()) {
                    --non_empty_buckets_count;
                }
                return;
            }
        }
    }

    size_t size() const {
        return total_elements;
    }

    bool empty() const {
        return total_elements == 0;
    }

    void forEach(std::function<void(const K&, V&)> func) {
        for (auto& bucket : hash_table) {
            for (auto& item : bucket) {
                func(item.first, item.second);
            }
        }
    }
};