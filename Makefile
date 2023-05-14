CFLAGS += -O1 -DNDEBUG -mavx2
CC = g++
OBJDIR = obj/
SRCDIR = src/

all: funcstest speedtest

funcstest: obj/funcstest.o obj/hashtable.o obj/hashfuncs.o obj/textfuncs.o obj/mystrcmp.o
	$(CC) obj/funcstest.o obj/hashtable.o obj/hashfuncs.o obj/textfuncs.o obj/mystrcmp.o -o $@

speedtest: obj/speedtest.o obj/hashtable.o obj/hashfuncs.o obj/textfuncs.o obj/mystrcmp.o
	$(CC) obj/speedtest.o obj/hashtable.o obj/hashfuncs.o obj/textfuncs.o obj/mystrcmp.o -o $@

obj/mystrcmp.o:
	nasm -felf64 -o obj/mystrcmp.o src/mystrcmp.asm

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm obj/*.o -f
	clear
	
.PHONY: clean