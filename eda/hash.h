/**
 * @file HashTable.h
 * @author ...
 * @brief Tabela hash com tratamento de colisão por encadeamento exterior.
 * Estrutura de Dados Avançada — 2025.1
 */

#ifndef CHAINED_HASHTABLE_HPP
#define CHAINED_HASHTABLE_HPP

#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <utility>
#include <functional>
#include <stdexcept>
#include <cctype>
using namespace std;

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class ChainedHashTable {
private:
    size_t m_number_of_elements;
    size_t m_table_size;
    float m_max_load_factor; 
    std::vector<std::list<std::pair<Key, Value>>> m_table;
    Hash m_hashing;
    int comparasons; 
    int collisions = 0;
    size_t get_next_prime(size_t x) {
        if (x <= 2) return 3;
        x = (x % 2 == 0) ? x + 1 : x;
        while (true) {
            bool not_prime = false;
            for (int i = 3; i <= std::sqrt(x); i += 2) {
                if (x % i == 0) {
                    not_prime = true;
                    break;
                }
            }
            if (!not_prime) return x;
            x += 2;
        }
    }

    size_t hash_code(const Key& k) const {
        return m_hashing(k) % m_table_size;
    }
   


public:
    ChainedHashTable(size_t tableSize = 19, float load_factor = 1.0)
        : m_number_of_elements(0) {
        m_table_size = get_next_prime(tableSize);
        m_table.resize(m_table_size);
        m_max_load_factor = (load_factor <= 0.0f) ? 1.0f : load_factor;
    }

    size_t size() const {
        return m_number_of_elements;
    }

    bool empty() const {
        return m_number_of_elements == 0;
    }

    size_t bucket_count() const {
        return m_table_size;
    }

    size_t bucket_size(size_t n) const {
        if (n >= m_table_size) throw std::out_of_range("invalid index");
        return m_table[n].size();
    }

    size_t bucket(const Key& k) const {
        return hash_code(k);
    }

    float load_factor() const {
        return static_cast<float>(m_number_of_elements) / m_table_size;
    }

    float max_load_factor() const {
        return m_max_load_factor;
    }

    void clear() {
        for (size_t i = 0; i < m_table_size; ++i) {
            m_table[i].clear();
        }
        m_number_of_elements = 0;
    }

    ~ChainedHashTable() = default;
void insert(const Key& k) {
    if (load_factor() >= m_max_load_factor) {
    collisions++;
        rehash(2 * m_table_size);
    }

    size_t slot = hash_code(k);

          for (auto& p : m_table[slot]) {
          comparasons++;
        if (p.first == k) {
            ++p.second;  
            return;
        }
        
    } 
    m_table[slot].push_back(std::make_pair(k, 1));
    ++m_number_of_elements;
}

    bool contains(const Key& k) {
        size_t slot = hash_code(k);
        for (const auto& p : m_table[slot]) {
            if (p.first == k) return true;
        }
        return false;
    }

    Value& at(const Key& k) {
        size_t slot = hash_code(k);
        for (auto& p : m_table[slot]) {
            if (p.first == k) return p.second;
        }
        throw std::out_of_range("key is not in the table");
    }

    void rehash(size_t m) {
        size_t new_table_size = get_next_prime(m);
        if (new_table_size <= m_table_size) return;

        std::vector<std::list<std::pair<Key, Value>>> new_table(new_table_size);
        for (size_t i = 0; i < m_table_size; ++i) {
            for (const auto& pair : m_table[i]) {
                size_t new_index = m_hashing(pair.first) % new_table_size;
                new_table[new_index].push_back(pair);
            }
        }
        m_table = std::move(new_table);
        m_table_size = new_table_size;
    }
    
  std::list<std::pair<Key, Value>>& bucket(size_t i)  { 
    return m_table[i];
}
    bool remove(const Key& k) {
        size_t slot = hash_code(k);
        auto& bucket = m_table[slot];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == k) {
                bucket.erase(it);
                --m_number_of_elements;
                return true;
            }
        }
        return false;
    }

    void reserve(size_t n) {
        if (n > m_table_size * m_max_load_factor) {
            rehash(static_cast<size_t>(n / m_max_load_factor) + 1);
        }
    }

    void set_max_load_factor(float lf) {
        if (lf <= 0.0f) throw std::out_of_range("Invalid load factor: must be > 0");
        m_max_load_factor = lf;
        reserve(m_number_of_elements);
    }

    Value& operator[](const Key& k) {
        size_t slot = hash_code(k);
        for (auto& p : m_table[slot]) {
            if (p.first == k) return p.second;
        }
        m_table[slot].push_back(std::make_pair(k, Value{}));
        ++m_number_of_elements;
        return m_table[slot].back().second;
    }

    const Value& operator[](const Key& k) const {
        size_t slot = hash_code(k);
        for (const auto& p : m_table[slot]) {
            if (p.first == k) return p.second;
        }
        throw std::out_of_range("key not found in const operator[]");
    }
    void write(ChainedHashTable<Key, Value>& dicionario, const std::string& arquivoSaida) {
    std::vector<std::pair<Key, Value>> vec;
    cout << "Deseja imprimir o dicionário completo ou palavras que começam com uma letra específica?\n";
    cout << "Digite 'completo', 'freq' ou uma letra (ex: a): ";
    string escolha;
    cin >> escolha;
    std::ofstream outFile(arquivoSaida);  // <<<<< LINHA FALTANDO

     if (escolha == "completo") {
          for (size_t i = 0; i < dicionario.bucket_count(); ++i) {
        auto& bucket = dicionario.bucket(i); 
        for (const auto& p : bucket) {
            vec.push_back(p);
        }
    }

    
    std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
    return a.first < b.first;  // ordena pela chave (string) em ordem crescente (alfabetica)
    });
     for (const auto& p : vec) {
        outFile << p.first << ": " << p.second << "\n";
    }
    } else if (escolha.size() == 1 && isalpha(escolha[0])) {
         for (size_t i = 0; i < dicionario.bucket_count(); ++i) {
        auto& bucket = dicionario.bucket(i); 
        for (const auto& p : bucket) {
       if (!p.first.empty() && std::tolower(p.first[0]) == std::tolower(escolha[0]))
            vec.push_back(p);
        }
    }

    std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
     for (const auto& p : vec) {
        outFile << p.first << ": " << p.second << "\n";
    }
    } else if(escolha == "freq") {
         
    for (size_t i = 0; i < dicionario.bucket_count(); ++i) {
        auto& bucket = dicionario.bucket(i);  
        for (const auto& p : bucket) {
            vec.push_back(p);
        }
    }

    std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
     for (const auto& p : vec) {
        outFile << p.first << ": " << p.second << "\n";
    }
    }
    
   
   
}
   int getComparisons(){
  return comparasons;
  }
  int getCollisions() const {
        return collisions;
    }

};

 

#endif 

