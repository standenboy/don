CFLAGS=-ggdb
CC=cc

svm1: svm1.c codegen.c checker.c tokenize.c types.c stack.c
	${CC} *.c -c ${CFLAGS}
	${CC} *.o -o svm1 ${CFLAGS}

install: svm1
	cp svm1 /usr/local/bin/svm1

uninstall: 
	rm /usr/local/bin/svm1

clean:
	rm -rf *.o svm1 test.ssa
