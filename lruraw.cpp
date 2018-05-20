// lru.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>
#include <list>

using namespace std;

/***********************************************************************
*                    Raw LRU Implementation                            *
***********************************************************************/
template<typename K, typename V>
struct Node {
	K key;
	V value;
	Node *prev, *next;
	Node(K _key, V _value) : key(_key), value(_value), prev(NULL), next(NULL) {}
};

template<typename K, typename V>
struct DoublyLinkedList {
	DoublyLinkedList(): front(NULL), rear(NULL), size(0) {}

	Node<K, V>* addPageToHead(K key, V value);
	void movePageToHead(Node<K, V>* page);

	bool isEmpty() { return rear == NULL; }
	size_t size;
	Node<K, V> *front, *rear;
};

template<typename K, typename V>
Node<K, V>* DoublyLinkedList<K, V>::addPageToHead(K key, V value) {
	Node<K,V> *page = new Node<K, V>(key, value);
	if(!front && !rear) {
		front = rear = page;
	} else {
		page->next = front;
		front->prev = page;
		front = page;
	}
	return page;
}

template<typename K, typename V>
void DoublyLinkedList<K, V>::movePageToHead(Node<K, V>* page) {
	if(page == front) { return; }

	if(page == rear) {
		rear = rear->prev;
		rear->next = NULL;
	} else {
		page->prev->next = page->next;
		page->next->prev = page->prev;
	}

	page->next = front;
	page->prev = NULL;
	front->prev = page;
	front = page;
}

template<typename K, typename V>
class RawLRU {
public:
	RawLRU(size_t _capacity);
	V get(K key);
	void put(K key, V value);
private:
	size_t capacity, size;
	unordered_map<K, Node<K, V>*> pageMap;
	DoublyLinkedList<K, V> *pageList;
};

template<typename K, typename V>
RawLRU<K, V>::RawLRU(size_t _capacity) : capacity(_capacity), size(0) {
	pageList = new DoublyLinkedList<K, V>();
}

template<typename K, typename V>
V RawLRU<K, V>::get(K key) {
	if(pageMap.find(key) == pageMap.end()) {
		throw std::range_error("Range error exception");
	}

	V val = pageMap[key]->value;

	pageList->movePageToHead(pageMap[key]);
	return val;
}

template<typename K, typename V>
void RawLRU<K, V>::put(K key, V value) {
	if(pageMap.find(key) != pageMap.end()) {
		return;
	}

	Node<K, V>* page = pageList->addPageToHead(key, value);
	size++;
	pageMap[key] = page;
}
