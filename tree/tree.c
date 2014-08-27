#include <stdio.h>

typedef struct node_s {
	void *data;
	void *child;
} node_t;

typedef struct ctrl_s {
	node_t *root;
	node_t *n;
}ctrl_t;

static node_t *search_node(node_t *root, unsigned int data)
{

}

void *init_tree(void) 
{
	return calloc(1, sizeof(ctrl_t));
}

void traverse_tree(void *ctrl_v, ttype_t type, int (*cb)(void *,
							void *), void *arg) 
{

}

static int compare_data(void *ctrl_v, void *data1, void *data2) 
{
	if (data1 == data2)
		return true;
	return false;
}

void add_node(void *ctrl_v, void *pdata, void *data) 
{
	ctrl_t *ctrl = (ctrl_t *)ctrl_v;
	node_t *n = NULL;

	traverse_tree(ctrl, BFS, compare_data, pdata);
	parent = ctrl->n;

	if (parent) {
		n = calloc(1, sizeof(node_t));
		n->child = init_list();
		n->data = data;
		add_node(parent->child, n, END);
	}

	return;
}

int main()
{

}

