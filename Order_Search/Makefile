all: search spawn

search: search.c utility.c utility.h
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o search search.c utility.c -lcs50 -lm

spawn: spawn.c
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o spawn spawn.c

clean:
	rm -f *.o a.out core search spawn
