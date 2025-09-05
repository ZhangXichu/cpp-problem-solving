// https://leetcode.com/problems/lru-cache/description/

#include <unordered_map>
#include <list>
#include <iostream>
#include <algorithm>

class LRUCache {

struct Node {
    int key;
    int value;
    Node* prev;
    Node* next;

    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};


public:
    LRUCache(int capacity)
        : _capacity(capacity) , _head(nullptr), _tail(nullptr)
    {}

    ~LRUCache() 
    {
        Node* current = _head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    
    int get(int key) 
    {
        if (_cache.find(key) == _cache.end()) {
            return -1;
        } 

        Node* node = _cache[key];

        remove(node);
        insert_front(node); // msu
        
        return node->value;
    }
    
    void put(int key, int value) 
    {
        if (_cache.find(key) == _cache.end()) { // new key

            Node* node = new Node(key, value);

            if (static_cast<int>(_cache.size()) < _capacity) // has  capacity
            {
                insert_front(node);
            } else { // no capacity

                Node* tmp = _tail;

                std::cout << "Evicting key: " << _tail->key << std::endl;

                remove(_tail);
                insert_front(node);

                _cache.erase(tmp->key);

                delete tmp;
            }

            _cache[key] = node;

        } else { // existing key
            remove(_cache[key]);
            insert_front(_cache[key]);
            
            _cache[key]->value = value;
        }

        print_cache();
        
    }

private:
    int _capacity;
    Node* _head;
    Node* _tail;

    std::unordered_map<int, Node*> _cache;

    void print_cache() {
        std::cout << "Cache size : " << _cache.size() << ", contents: ";

        for (const auto& pair : _cache) {
            std::cout << "{" << pair.first << ": " << pair.second->value << "} ";
        }
        std::cout << std::endl;
    }

    void insert_front(Node* node)
    {
        if (!_head) {
            _head = node;
            _tail = node;
        } else {
            node->next = _head;
            _head->prev = node;
            _head = node;
        }
    }

    void remove(Node* node)
    {
        if (!_head)
            return;
        if (_head == _tail && _head == node) {
            _head = nullptr;
            _tail = nullptr;
        } else if (node == _head) {
            _head = _head->next;
            if (_head) _head->prev = nullptr;
        } else if (node == _tail) {
            _tail = _tail->prev;
            if (_tail) _tail->next = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
    }
    
};


int main()
{
    LRUCache lru(2);
    lru.put(1, 1);
    lru.put(2, 2);
    std::cout << lru.get(1) << std::endl;
    lru.put(3, 3);
    std::cout << lru.get(2) << std::endl;
    lru.put(4, 4);
    std::cout << lru.get(1) << std::endl;
    std::cout << lru.get(3) << std::endl;
    std::cout << lru.get(4) << std::endl;


    return 0;
}