#include <stdio.h>
#include <stdlib.h>

typedef struct node_s {
	void *data;
	struct node_s *left;
	struct node_s *right;
	struct node_s *parent;
} node_t;

void _height(node_t *n, int h, int *max)
{
	if (!n)
		return;
	_height(n->left, h, max);
	h += 1;
	if (*max < h)
		*max = h;
	_height(n->right, h, max);
}

int height_tree(node_t *n)
{
	int max = 0;
	_height(n, 0, &max);
	return max;
}

void left_rotate(node_t *n)
{
	node_t *parent = n->parent;
	if 

	assert (parent->right == n);
	

	
}

int avl_check(node_t *n)
{
	if ((height_tree(n->left) - height_tree(n->right)) 

}

void *add_node(node_t *root, void *data)
{
	node_t *n = NULL;
	n = (node_t *)calloc(1, sizeof(node_t));
	n->data = data;
	if (n) {
		node_t *t = root;
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
				root = n;
				break;
			}
		}
	}
	return n;
}

void *traverse_tree(node_t *n, int (*cb)(void *, void *), void *arg)
{
	node_t *t = NULL;
	if (n == NULL)
		return n;

	if ((t = traverse_tree(n->left, cb, arg)) != NULL)
		return t;
	if (cb(n->data, arg))
		return n;
	if ((t = traverse_tree(n->right, cb, arg)) != NULL)
		return t;
}
