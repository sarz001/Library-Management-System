#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <cstring> // For strcmp if needed
#include <iostream>

template <typename K, typename V>
class HashTable {
private:
    struct Entry {
        K key;
        V value;
        bool occupied;
        bool deleted;
        Entry() : occupied(false), deleted(false) {}
    };

    Entry* table;
    int capacity;
    int count;

    int hash(const K& key) const {
        int h = 0;
        for (size_t i = 0; i < key.size(); ++i)
            h = 31 * h + key[i];
        return h & 0x7fffffff;
    }

    void rehash() {
        int oldCap = capacity;
        Entry* oldTable = table;

        capacity *= 2;
        table = new Entry[capacity];
        count = 0;

        for (int i = 0; i < oldCap; ++i) {
            if (oldTable[i].occupied && !oldTable[i].deleted) {
                insert(oldTable[i].key, oldTable[i].value);
            }
        }

        delete[] oldTable;
    }

public:
    HashTable(int initialCap = 101) {
        capacity = initialCap;
        table = new Entry[capacity];
        count = 0;
    }

    ~HashTable() {
        delete[] table;
    }

    void insertToList(const K& key, const typename V::value_type& element) {
        V* existing = get(key);
        if (existing == nullptr) {
            V list;
            list.push_back(element);
            insert(key, list);
        } else {
            existing->push_back(element);
        }
    }

    V* get(const K& key) {
        int idx = hash(key) % capacity;
        int startIdx = idx;
        while (table[idx].occupied) {
            if (!table[idx].deleted && table[idx].key == key) {
                return &table[idx].value;
            }
            idx = (idx + 1) % capacity;
            if (idx == startIdx) break;
        }
        return nullptr;
    }    

    void insert(const K& key, const V& value) {
        if ((count + 1) * 2 >= capacity)
            rehash();

        int idx = hash(key) % capacity;
        while (table[idx].occupied && !table[idx].deleted && table[idx].key != key)
            idx = (idx + 1) % capacity;

        if (!table[idx].occupied || table[idx].deleted) {
            count++;
        }

        table[idx].key = key;
        table[idx].value = value;
        table[idx].occupied = true;
        table[idx].deleted = false;
    }

    bool find(const K& key, V& outVal) const {
        int idx = hash(key) % capacity;
        int startIdx = idx;
        while (table[idx].occupied) {
            if (!table[idx].deleted && table[idx].key == key) {
                outVal = table[idx].value;
                return true;
            }
            idx = (idx + 1) % capacity;
            if (idx == startIdx) break;
        }
        return false;
    }

    bool exists(const K& key) const {
        V dummy;
        return find(key, dummy);
    }

    void remove(const K& key) {
        int idx = hash(key) % capacity;
        while (table[idx].occupied) {
            if (!table[idx].deleted && table[idx].key == key) {
                table[idx].deleted = true;
                return;
            }
            idx = (idx + 1) % capacity;
        }
    }

    // ✅ New: Get pointer to value (for use in Library.cpp)
    V* get(const K& key) {
        int idx = hash(key) % capacity;
        int startIdx = idx;
        while (table[idx].occupied) {
            if (!table[idx].deleted && table[idx].key == key) {
                return &table[idx].value;
            }
            idx = (idx + 1) % capacity;
            if (idx == startIdx) break;
        }
        return nullptr;
    }

    // ✅ New: Insert to list-type value (e.g., DynamicArray<Book>)
    void insertToList(const K& key, const typename V::value_type& element) {
        V* list = get(key);
        if (list == nullptr) {
            V newList;
            newList.push_back(element);
            insert(key, newList);
        } else {
            list->push_back(element);
        }
    }
};

#endif // HASH_TABLE_H
