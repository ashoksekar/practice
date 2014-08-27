#include <stdio.h>
#include <stdlib.h>

typedef struct node_s {
	unsigned int data;
	struct node_s *left;
	struct node_s *right;
	struct node_s *parent;
} node_t;

static void add_node(node_t **root, unsigned int data)
{
	node_t *n = NULL;
	n = (node_t *)calloc(1, sizeof(node_t));
	n->data = data;
	if (n) {
		node_t *t = *root;
		while(1) {
			if (t) {
				if (data > t->data) {
					if (t->right)
						t = t->right;
					else {
						t->right = n;
						n->parent = t;
						break;
					}
				}
				else {
					if (t->left)
						t = t->left;
					else {
						t->left = n;
						n->parent = t;
						break;
					}
				}
			}
			else {
				*root = n;
				break;
			}
		}
	}
	return;
}
static void print_tree(node_t *n)
{
	if (n == NULL)
		return;
	print_tree(n->left);
	printf ("%d ", n->data);
	print_tree(n->right);
}

int main()
{
	node_t *root = NULL;
	int opt = 0;
	while (1) {
		printf ("1. Add node\n");
		printf ("2. Print tree\n");
		printf ("3. Exit\n");
		printf ("Enter your option: ");
		scanf("%d",&opt);
		switch (opt) {
			unsigned int data;
			case 1:
				printf ("Enter data: ");
				scanf("%u",&data);
				add_node(&root, data);
				break;
			case 2:
				print_tree(root);
				printf ("\n");
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

