
CC_FLAGS=-g
#########################
LIB=libsudt.a

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))

$(LIB) : $(OBJS)
	ar -rc $@ $^

.PHONY: clean

clean:
	@rm -vf $(OBJS) $(LIB)
