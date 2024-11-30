#pragma once
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

    std::vector<std::forward_list<value_type>> hash_table;
    size_t non_empty_buckets_count;
    size_t total_elements;

    float load_factor;

    void rehash() {
        if ((float) non_empty_buckets_count / get_bucket_count() > load_factor) {
            size_t new_size = std::max(hash_table.size() * 2, size_t(2)); 
            std::vector<std::forward_list<value_type>> new_table(new_size);
            size_t new_non_empty = 0;
            size_t new_total = 0;
            for (auto& bucket : hash_table) {
                for (auto& item : bucket) {
                    size_t hash = Hash{}(item.first);
                    size_t index = hash % new_size; 
                    if (bucket_size(new_table[index]) == 0) {
                        ++new_non_empty;
                    }
                    new_table[index].emplace_front(std::move(item));
                    ++new_total;
                }
            }
            hash_table = std::move(new_table);
            non_empty_buckets_count = new_non_empty;
            total_elements = new_total;
        }
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

        return hash_table[index].front().second;
    }

    size_t bucket_size(const std::forward_list<value_type>& bucket) const {
        return std::distance(bucket.begin(), bucket.end());
    }

    size_t get_bucket_count() const {
        return hash_table.size();
    }

    size_t get_index_from_hash(size_t hash) const {
        return hash % get_bucket_count();
    }

public:
    HashMap(float lf = 0.5f) : hash_table(2), non_empty_buckets_count(0), total_elements(0), load_factor(lf) {}

    HashMap(const HashMap& other) : hash_table(other.get_bucket_count()), non_empty_buckets_count(0), total_elements(0), load_factor(other.load_factor) {
        for (const auto& bucket : other.hash_table) {
            for (const auto& item : bucket) {
                size_t hash = Hash{}(item.first);
                size_t index = get_index_from_hash(hash);
                if (bucket_size(hash_table[index]) == 1) {
                    ++non_empty_buckets_count;
                }
                hash_table[index].emplace_front(item);
                ++total_elements;
            }
        }
        rehash();
    }

    HashMap(HashMap&& other) noexcept : hash_table(std::move(other.hash_table)), non_empty_buckets_count(other.non_empty_buckets_count), total_elements(other.total_elements), load_factor(other.load_factor) {
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
            load_factor = other.load_factor;
            other.non_empty_buckets_count = 0;
            other.total_elements = 0;
        }
        return *this;
    }

    V& operator[](const K& key) {
        return insert_or_get(K(key));  //вот тут плохо
    }

    V& operator[](K&& key) {
        return insert_or_get(std::move(key));  
    }


    ~HashMap() = default;

    void swap(HashMap& other) {
        hash_table.swap(other.hash_table);
        std::swap(non_empty_buckets_count, other.non_empty_buckets_count);
        std::swap(total_elements, other.total_elements);
        std::swap(load_factor, other.load_factor);
    }

    std::optional<std::reference_wrapper<value_type>> find(const K& k) {
        size_t hash = Hash{}(k);
        std::cout << "hash" << hash<< "\n";
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
        auto it = bucket.before_begin();
        for (auto next = bucket.begin(); next != bucket.end(); ) {
            if (next->first == k) {
                next = bucket.erase_after(it);
                --total_elements;
            } else {
                ++it;
                ++next;
            }
        }
        if (bucket.empty()) {
            --non_empty_buckets_count;
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