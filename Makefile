
C_FLAGS=-g
#########################
LIB=libsudt.a
BENCH=bench/bench

.PHONY: all
all: $(BENCH) $(LIB)

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))

bench/bench.o: bench/bench.c
	cc -I./ -c $^ -o $@

$(BENCH) : $(OBJS) bench/bench.o
	cc $^ -o $@

$(LIB) : $(OBJS)
	ar -rc $@ $^


.PHONY: clean
clean:
	@rm -vf $(OBJS) $(LIB) bench/bench.o $(BENCH)
