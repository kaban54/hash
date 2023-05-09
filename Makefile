CFLAGS += -O1 -DNDEBUG
CC = g++
OBJDIR = obj/
SRCDIR = src/

funcstest: obj/funcstest.o obj/hashtable.o obj/hashfuncs.o obj/textfuncs.o
	$(CC) obj/funcstest.o obj/hashtable.o obj/hashfuncs.o obj/textfuncs.o -o $@.exe

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm obj/*.o -f
	clear
	
.PHONY: clean