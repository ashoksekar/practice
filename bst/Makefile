all: bst_demo

bst.o: bst.c
	gcc -c -g -o $@ $^

bst_demo: bst.o bst_demo.c
	gcc -o $@ -g -I./ $^  
