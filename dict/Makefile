all: dict

list.o: ../list/list.c
	gcc -c -g -o $@ $^

tree.o: ../tree/tree.c
	gcc -c -g -I../list/ -I../tree/ -o $@ $^

dict: list.o tree.o dict.c
	gcc -o $@ -g -I../list/ -I./ -I../tree/ $^  

