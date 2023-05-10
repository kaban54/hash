CFLAGS += -O1 -DNDEBUG
CC = g++
OBJDIR = obj/
SRCDIR = src/

all: funcstest speedtest

funcstest: obj/funcstest.o obj/hashtable.o obj/hashfuncs.o obj/textfuncs.o
	$(CC) obj/funcstest.o obj/hashtable.o obj/hashfuncs.o obj/textfuncs.o -o $@

speedtest: obj/speedtest.o obj/hashtable.o obj/hashfuncs.o obj/textfuncs.o
	$(CC) obj/speedtest.o obj/hashtable.o obj/hashfuncs.o obj/textfuncs.o -o $@

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm obj/*.o -f
	clear
	
.PHONY: clean