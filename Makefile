main: lru.o lrustl.o lruraw.o
	g++ -o lru -std=c++14 lru.o lrustl.o lruraw.o

main.o: lru.cpp
	g++ -c -std=c++14 main.cpp

lrustl.o: lrustl.cpp
	g++ -c -std=c++14 lrustl.cpp

lruraw.o: lruraw.cpp
	g++ -c -std=c++14 lruraw.cpp

clean:
	rm lru.o lrustl.o lruraw.o
