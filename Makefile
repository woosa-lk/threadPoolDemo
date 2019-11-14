CC = gcc
CFLAGS = -g -Wall -o2
LIB = -lpthread

RUNE = $(CC) $(CFLAGS) $(object) -o $(exe) $(LIB)
RUNO = $(CC) $(CFLAGS) -c $< -o $@ $(LIB)

.RHONY:clean


object = main.o threadpool.o
exe = cThreadpool

$(exe):$(object)
	$(RUNE)

%.o:%.c threadpool.h
	$(RUNO)
%.o:%.c
	$(RUNO)


clean:
	-rm -rf *.o cThreadpool *~