all: tree_demo

list.o: ../list/list.c
	gcc -c -g -o $@ $^

tree.o: tree.c
	gcc -c -g -I../list/ -o $@ $^

tree_demo: list.o tree.o tree_demo.c
	gcc -o $@ -g -I../list/ -I./ $^  

