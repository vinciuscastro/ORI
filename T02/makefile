ORI_T02: ORI_T02.o
	gcc ORI_T02.o -g -o ORI_T02

ORI_T02_HEADER.o: ORI_T02_HEADER.h
	gcc -g -c ORI_T02_HEADER.c

ORI_T02.o: ORI_T02.c ORI_T02_HEADER.o
	gcc -g -c ORI_T02.c

clean:
	rm ORI_T02 *.o
