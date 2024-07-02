#include <iostream>
#include <unordered_map>
#include <list>
#include<unordered_map>

using namespace std;

struct DLinkedNode {
    int key, value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value) : key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    unordered_map<int, DLinkedNode*> cache;
    DLinkedNode* head;
    DLinkedNode* tail;
    int size;
    int capacity;

public:
    LRUCache(int _capacity) : capacity(_capacity), size(0) {
        // ʹ��αͷ����αβ���ڵ�
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        // ��� key ���ڣ���ͨ����ϣ����λ�����Ƶ�ͷ��
        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value) {
        if (!cache.count(key)) {
            // ��� key �����ڣ�����һ���µĽڵ�
            DLinkedNode* node = new DLinkedNode(key, value);
            // ���ӽ���ϣ��
            cache[key] = node;
            // ������˫��������ͷ��
            addToHead(node);
            ++size;
            if (size > capacity) {
                // �������������ɾ��˫��������β���ڵ�
                DLinkedNode* removed = removeTail();
                // ɾ����ϣ���ж�Ӧ����
                cache.erase(removed->key);
                // ��ֹ�ڴ�й©
                delete removed;
                --size;
            }
        }
        else {
            // ��� key ���ڣ���ͨ����ϣ����λ�����޸� value�����Ƶ�ͷ��
            DLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }

    void addToHead(DLinkedNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(DLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(DLinkedNode* node) {
        removeNode(node);
        addToHead(node);
    }

    DLinkedNode* removeTail() {
        DLinkedNode* node = tail->prev;
        removeNode(node);
        return node;
    }
};


int main() {
    LRUCache cache(2);
    cache.put(1, 1); // ������ {1=1}
    std::cout << cache.get(1) << std::endl; // ���� 1
    cache.put(2, 2); // ������ {1=1, 2=2}
    std::cout << cache.get(2) << std::endl; // ���� 2
    cache.put(3, 3); // 3 �滻�˼� 1�������� {2=2, 3=3}
    std::cout << cache.get(1) << std::endl; // ���� -1 (δ�ҵ�)
    std::cout << cache.get(3) << std::endl; // ���� 3
    cache.put(4, 4); // 4 �滻�˼� 2�������� {3=3, 4=4}
    std::cout << cache.get(2) << std::endl; // ���� -1 (δ�ҵ�)
    return 0;
}