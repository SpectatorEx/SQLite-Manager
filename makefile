MKDIR := mkdir.exe
RM := rm.exe

SRCS := $(wildcard src/*.c src/*/*.c src/*/*/*.c)
OBJS := $(patsubst src/%.c, obj/%.o, $(SRCS)) 

INCS := -Iinc -Iinc/system

CFLAGS := -Wall -std=c99

obj/%.o: src/%.c
	$(MKDIR) -p $(@D)
	gcc $(CFLAGS) $(INCS) -c $< -o $@

compile_release: $(OBJS)
	$(MKDIR) -p bin
	gcc -s -o bin/SQLiteManager $(OBJS) bin/sqlite3.dll

clean:
	$(RM) -r obj/*