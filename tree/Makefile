all: tree_demo

list.o: ../ll/list.c
	gcc -c -g -o $@ $^

tree.o: tree.c
	gcc -c -g -I../ll/ -o $@ $^

tree_demo: list.o tree.o tree_demo.c
	gcc -o $@ -g -I../ll/ -I./ $^  

