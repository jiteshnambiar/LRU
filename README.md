# lru cache

A cache object that deletes the least-recently-used items.

C++ based implementation using STL.

## Usage:
```
/**Create cache with maximum size of two. When the cache is full every new element will replace the least recently used one */

	StlLRU<int, string> cache(2);
	cache.put(2, "hello");
	cout << cache.get(2) << endl;
	try{
		cout << cache.get(1) << endl;
	} catch(exception err) {
		cout << err.what() << endl;
	}

	cache.put(1, "world");
	cache.put(1, "universe");
	cout << cache.get(1) << endl;
	cout << cache.get(2) << endl;

	cache.put(8, "apples");
	try{
		cout << cache.get(1) << endl;
	} catch(exception err) {
		cout << err.what() << endl;
	}
	cout << cache.get(8) << endl;
```

## How to run:

```
make
./lru
```
