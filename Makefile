CFLAGS += -O1 -DNDEBUG
CC = g++


obj/hashtable.o: src/hashtable.cpp
	$(CC) -o obj/hashtable.o src/hashtable.cpp -c $(CFLAGS)

obj/hashfuncs.o: src/hashfuncs.cpp
	$(CC) -o obj/hashfuncs.o src/hashfuncs.cpp -c $(CFLAGS)

clean:
	rm obj/*.o -f
	clear
	
.PHONY: clean