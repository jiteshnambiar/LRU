#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>
#include <list>
using namespace std;

/***********************************************************************
*                    STL LRU Implementation                            *
***********************************************************************/
template<typename K, typename V>
class StlLRU {
public:
	typedef typename std::pair<K, V> T_KeyValuePair;
	typedef typename std::list<T_KeyValuePair>::iterator T_PageIterator;

	StlLRU(size_t _maxSize) : maxSize(_maxSize) {}
	V& get(const K& key);
	void put(const K& key, const V& value);
private:
	size_t maxSize;
	std::list<T_KeyValuePair> pages;
	std::unordered_map<K, T_PageIterator> pageMap;
};

template<typename K, typename V>
V& StlLRU<K, V>::get(const K& key) {
	auto it = pageMap.find(key);
	if(it == pageMap.end()) {
		throw range_error("No such key in cache");
	}
	pages.push_front(T_KeyValuePair(it->second->first, it->second->second));
	pages.erase(it->second);
	pageMap[key] = pages.begin();
	return pages.front().second;
}

template<typename K, typename V>
void StlLRU<K, V>::put(const K& key, const V& value) {
	auto it = pageMap.find(key);
	pages.push_front(T_KeyValuePair(key, value));
	if(it != pageMap.end()) {
		pages.erase(it->second);
		pageMap.erase(it);
	}
	pageMap[key] = pages.begin();

	if(pageMap.size() > maxSize) {
		auto last = pages.end();
		last = prev(last, 1);
		pageMap.erase(last->first);
		pages.pop_back();
	}
}
