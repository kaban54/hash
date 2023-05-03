CFLAGS += -O1
CC = g++


obj/hashtable.o: src/hashtable.cpp
	$(CC) -o obj/hashtable.o src/hashtable.cpp -c $(CFLAGS)

clean:
	rm obj/*.o -f
	clear
	
.PHONY: clean