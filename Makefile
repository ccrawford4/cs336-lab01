PROG = part1 part2 part3

part1_OBJS = part1.o
part2_OBJS = part2.o
part3_OBJS = part3.o

OBJS = $(part1_OBJS) $(part2_OBJS) $(part3_OBJS)

%.o: %.c
	gcc -g -c -o $@ $<

all: $(PROG)

part1: $(part1_OBJS)
	gcc -g -o $@ $^

part2: $(part2_OBJS)
	gcc -std=c99 -o $@ $^ -lcrypt

part3: $(part3_OBJS)
	gcc -g -o $@ $^

clean:
	rm -rf $(PROG) $(OBJS)
