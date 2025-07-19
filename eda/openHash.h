template <typename Key, typename Value>
class HashOpen {
private:
    enum EntryState { EMPTY, OCCUPIED, DELETED };

    struct Entry {
        Key key;
        Value value;
        EntryState state;

        Entry() : state(EMPTY) {}
        Entry(const Key& k, const Value& v) : key(k), value(v), state(OCCUPIED) {}
    };

    std::vector<Entry> table;
    size_t m_size;
    size_t m_capacity;
    int  comparisons;

    size_t hash(const Key& key) const {
        return std::hash<Key>{}(key) % m_capacity;
    }
    
    size_t probe(const Key& key, size_t i) const {
       
        return (hash(key) + i) % m_capacity;
    }

public:
    HashOpen(size_t capacity = 101) : table(capacity), m_size(0), m_capacity(capacity) {}

    bool insert(const Key& key, const Value& value) {
        if (m_size >= m_capacity * 0.7) { // load factor max 0.7
            rehash(m_capacity * 2);
        }

        for (size_t i = 0; i < m_capacity; ++i) {
            size_t idx = probe(key, i);
             comparisons++;
            if (table[idx].state == EMPTY || table[idx].state == DELETED) {
                table[idx] = Entry(key, value);
                ++m_size;
                return true;
            } 
             else if (table[idx].state == OCCUPIED && table[idx].key == key) {
                table[idx].value = value; 
                return true;
            }
        }
        return false;
    }

    bool remove(const Key& key) {
        for (size_t i = 0; i < m_capacity; ++i) {
            size_t idx = probe(key, i);
            if (table[idx].state == EMPTY) return false; // não achou

            if (table[idx].state == OCCUPIED && table[idx].key == key) {
                table[idx].state = DELETED;
                --m_size;
                return true;
            }
        }
        return false;
    }

    bool find(const Key& key, Value& value_out) const {
        for (size_t i = 0; i < m_capacity; ++i) {
            size_t idx = probe(key, i);
            if (table[idx].state == EMPTY) return false; // não achou

            if (table[idx].state == OCCUPIED && table[idx].key == key) {
                value_out = table[idx].value;
                return true;
            }
        }
        return false;
    }
    int  getComparisons()  {
        return comparisons;
    }
    size_t size() const {
    return m_size;
}
std::vector<std::pair<Key, Value>> getAllWords() const {
    std::vector<std::pair<Key, Value>> result;
    for (const auto& entry : table) {
        if (entry.state == OCCUPIED) {
            result.emplace_back(entry.key, entry.value);
        }
    }
    return result;
}


private:
    void rehash(size_t new_capacity) {
        std::vector<Entry> old_table = std::move(table);
        table = std::vector<Entry>(new_capacity);
        m_capacity = new_capacity;
        m_size = 0;

        for (const auto& entry : old_table) {
            if (entry.state == OCCUPIED) {
                insert(entry.key, entry.value);
            }
        }
    }
};
