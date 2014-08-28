#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include "tree.h"

typedef struct node_s {
	void *data;
	void *child;
} tnode_t;

typedef struct ctrl_s {
	tnode_t *root;
}tctrl_t;

void *tree_init(void) 
{
	return calloc(1, sizeof(tctrl_t));
}

static void *tree_traverse_bfs(tctrl_t *ctrl, void *queue, int (*cb)(void *,
							   void *), void *arg)
{
	tnode_t *n = NULL;
	
	while ((n = list_remove_node(queue, TAIL)) != NULL) 
	{
		if (cb(n->data, arg))
			break;
		if (n->child)
			list_append(queue, n->child, STRAIGHT, HEAD);
	}
	return n;

}
static void *tree_traverse_dfs(tctrl_t *ctrl, void *stack, int (*cb)(void *,
							   void *), void *arg)
{
	tnode_t *n = NULL;
	
	while ((n = list_remove_node(stack, HEAD)) != NULL) 
	{
		if (cb(n->data, arg))
			break;
		if (n->child)
			list_append(stack, n->child, REVERSE, HEAD);
	}
	return n;

}


void *tree_traverse(void *ctrl_v, ttype_t type, int (*cb)(void *,
							void *), void *arg) 
{
	void *ret = NULL;
	tctrl_t *ctrl = (tctrl_t *)ctrl_v;
	if (!ctrl->root)
		return ret;

	if (type == BFS) {
		void *queue = list_init();
		list_add_node(queue, ctrl->root, HEAD);
		ret = tree_traverse_bfs(ctrl, queue, cb, arg);
		list_free(queue);
	}
	else if (type == DFS) {
		void *stack = list_init();
		list_add_node(stack, ctrl->root, HEAD);
		ret = tree_traverse_dfs(ctrl, stack, cb, arg);
		list_free(stack);
	}
	return ret;
}

void tree_free(void *ctrl_v)
{

}

void tree_add_node(void *ctrl_v, void *pnode, void *data) 
{
	tctrl_t *ctrl = (tctrl_t *)ctrl_v;
	tnode_t *n = NULL, *parent = NULL;

	parent = (tnode_t *)pnode;

	n = calloc(1, sizeof(tnode_t));
	n->child = list_init();
	n->data = data;
	if (parent) {
		list_add_node(parent->child, n, HEAD);
	}
	else {
		ctrl->root = n;
	}

	return;
}


