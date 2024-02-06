PROG = lab1Struct labFileIO lab1BitwiseOp

lab1Struct_OBJS = lab1Struct.o
labFileIO_OBJS = labFileIO.o
lab1BitwiseOp_OBJS = lab1BitwiseOp.o

OBJS = $(lab1Struct_OBJS) $(labFileIO_OBJS) $(lab1BitwiseOp_OBJS)

%.o: %.c
	gcc -g -c -o $@ $<

all: $(PROG)

lab1Struct: $(lab1Struct_OBJS)
	gcc -g -o $@ $^

labFileIO: $(labFileIO_OBJS)
	gcc -g -o $@ $^

lab1BitwiseOp: $(lab1BitwiseOp_OBJS)
	gcc -g -o $@ $^

clean:
	rm -rf $(PROG) $(OBJS)
