all: clFtp.c srvFtp.c
	gcc -g -Wall clFtp.c -o  clFtp
	gcc -g -Wall srvFtp.c -o srvFtp
clean:
	$(RM) clFtp srvFtp
