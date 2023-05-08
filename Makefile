CFLAGS += -O1 -DNDEBUG
CC = g++
OBJDIR = obj/
SRCDIR = src/

test1: obj/test1.o obj/hashtable.o obj/hashfuncs.o obj/textfuncs.o
	$(CC) obj/test1.o obj/hashtable.o obj/hashfuncs.o obj/textfuncs.o -o $@.exe

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm obj/*.o -f
	clear
	
.PHONY: clean