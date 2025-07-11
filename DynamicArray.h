#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <type_traits>

// Generic HashTable implementation
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
        for (char ch : key) {
            h = 31 * h + ch;
        }
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

    bool exists(const K& key) const {
        int idx = hash(key) % capacity;
        int startIdx = idx;
        while (table[idx].occupied) {
            if (!table[idx].deleted && table[idx].key == key) {
                return true;
            }
            idx = (idx + 1) % capacity;
            if (idx == startIdx) break;
        }
        return false;
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

    // Only enabled if V has a value_type and push_back()
    template <typename U = V>
    typename std::enable_if<
        std::is_class<typename U::value_type>::value &&
        std::is_member_function_pointer<decltype(&U::push_back)>::value,
        void
    >::type
    insertToList(const K& key, const typename U::value_type& element) {
        U* existingList = get(key);
        if (existingList == nullptr) {
            U newList;
            newList.push_back(element);
            insert(key, newList);
        } else {
            existingList->push_back(element);
        }
    }
};

#endif // HASH_TABLE_H
