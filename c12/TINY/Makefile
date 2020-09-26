TINY: tiny.c csapp.c
	gcc -O2 -o TINY tiny.c csapp.c -lpthread
TINY_6: tiny_6.c csapp.c
	gcc -O2 -o TINY_6 tiny_6.c csapp.c -lpthread
adder: adder.c csapp.c
	gcc -O2 -o web/cgi-bin/adder adder.c csapp.c -lpthread
TINY-PROC: tiny-proc.c csapp.c
	gcc -O2 -o TINY-PROC tiny-proc.c csapp.c -lpthread
TINY-SELECT: tiny-select.c pool.c csapp.c
	gcc -Og -o TINY-SELECT tiny-select.c pool.c csapp.c -lpthread
TINY-THREAD: tiny-thread.c csapp.c
	gcc -O2 -o TINY-THREAD tiny-thread.c csapp.c -lpthread
TINY-SBUF: tiny-sbuf.c sbuf.c csapp.c sbuf.h
	gcc -O2 -o TINY-SBUF tiny-sbuf.c sbuf.c csapp.c -lpthread
TINY-SBUF-B: tiny-sbuf-b.c sbuf-b.c csapp.c sbuf-b.h
	gcc -O2 -o TINY-SBUF-B tiny-sbuf-b.c sbuf-b.c csapp.c -lpthread
all: TINY TINY_6 adder TINY-PROC TINY-SELECT TINY-THREAD TINY-SBUF

.PHONY: clean
clean:
	rm TINY*
