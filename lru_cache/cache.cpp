#include <unordered_map>
#include <list>
#include <iostream>
#include <algorithm>

class LRUCache {  // TODO: improve time complexity
public:
    LRUCache(int capacity)
        : _capacity(capacity) 
    {}
    
    int get(int key) 
    {
        if (_cache.find(key) == _cache.end()) {
            return -1;
        } 

        _keys.erase(std::find(_keys.begin(), _keys.end(), key));
        _keys.push_front(key); //msu

        return _cache[key];
    }
    
    void put(int key, int value) 
    {
        if (_cache.find(key) == _cache.end()) { // new key

            if (static_cast<int>(_cache.size()) < _capacity) // has  capacity
            {
                _keys.push_front(key);
            } else { // no capacity
                _cache.erase(_keys.back());
                _keys.pop_back();
                _keys.push_front(key);
            }

        } else { // existing key
            _keys.erase(std::find(_keys.begin(), _keys.end(), key));
            _keys.push_front(key); //msu
        }

        _cache[key] = value;

        print_cache();
        
    }

private:
    int _capacity;
    std::unordered_map<int, int> _cache;
    std::list<int> _keys;

    void print_cache() {
        std::cout << "Cache size : " << _cache.size() << ", contents: ";

        for (const auto& pair : _cache) {
            std::cout << "{" << pair.first << ": " << pair.second << "} ";
        }
        std::cout << std::endl;
    }
    
};


int main()
{
    LRUCache lru(2);
    std::cout << lru.get(2) << std::endl;
    lru.put(2, 6);
    std::cout << lru.get(1) << std::endl;
    lru.put(1, 5);
    lru.put(1, 2);
    std::cout << lru.get(1) << std::endl;
    std::cout << lru.get(2) << std::endl;

    return 0;
}