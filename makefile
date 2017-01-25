C=gcc
RM=rm -f
CFLAGS=-O3 -mavx2 -g -funroll-all-loops -Wall
SRCS=main.c sha256.c sha256avx.c
OBJS=$(subst .c,.o,$(SRCS))
OUTFILE="sha256"

all: sha256

sha256: $(OBJS)
	$(C) -o $(OUTFILE) $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(C) $(CFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend
