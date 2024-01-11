CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic

all: cacher

cacher: cacher.o cache.o
	$(CC) -o cacher cacher.o cache.o

cacher.o: cacher.c
	$(CC) $(CFLAGS) -c cacher.c

cache.o: cache.c
	$(CC) $(CFLAGS) -c cache.c

clean:
	rm -f cacher *.o

format:
	clang-format -i -style=file *.[ch]
