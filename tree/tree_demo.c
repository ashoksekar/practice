#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include <tree.h>
#include <assert.h>

static int compare_data(void *ndata, void *arg)
{
	if (!ndata || !arg)
		return 0;
	if (*(int *)ndata == *(int *)arg)
		return 1;
	return 0;
}
static int print_tree(void *ndata, void *arg)
{
	if (!ndata)
		return 0;
	printf ("%d ", *(int *)ndata);
	return 0;
}

int main()
{
	int choice = 0;
	void *root = NULL;
	while (1) {

		printf ("1. Add node\n");
		printf ("2. Print tree in BFS\n");
		printf ("3. Print tree in DFS\n");
		printf ("4. Exit\n");
		printf ("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				{
					int *data = NULL, parent;
					void *pnode = NULL, *n = NULL;

					printf ("Enter parent: ");
					scanf ("%d", &parent);
					pnode = tree_traverse(root, BFS, compare_data, &parent);
					if (!pnode)
					{
						assert(!root);
					}
					data = (int *)calloc (1, sizeof(*data));
					printf ("Enter data: ");
					scanf ("%d", data);
					n = tree_add_node(root, pnode, data);
					if (!root)
						root = n;
				}
				break;
			case 2:
				tree_traverse(root, BFS, print_tree, NULL);
				printf ("\n");
				break;
			case 3:
				tree_traverse(root, DFS, print_tree, NULL);
				printf ("\n");
				break;
			case 4:
				exit(0);
				break;
			default:
				printf ("Invalid choice!\n");
				break;
		}
	}
}
