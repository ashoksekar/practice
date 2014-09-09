#include <stdio.h>
#include <stdlib.h>
#include <bst.h>

int print_node(void *data, void *arg)
{
	unsigned int *d = (unsigned int *)data;
	printf ("%d ", *d);
	return 0;
}

int main()
{
	void *root = NULL, *n = NULL;
	int opt = 0;
	while (1) {
		printf ("1. Add node\n");
		printf ("2. Print tree\n");
		printf ("3. Exit\n");
		printf ("Enter your option: ");
		scanf("%d",&opt);
		switch (opt) {
			unsigned int data, *d = NULL;
			case 1:
				printf ("Enter data: ");
				scanf("%u",&data);
				d = calloc(1, sizeof(*d));
				*d = data;
				n = add_node(root, d);
				if (!root)
					root = n;
				break;
			case 2:
				traverse_tree(root, print_node, NULL);
				printf ("\n");
				printf ("Height of the tree: %d\n", height_tree(root));
				break;
			case 3:
				exit(0);
				break;
			default:
				printf ("Unrecognized option!\n");
				break;
		}
	}
	return 0;

}

