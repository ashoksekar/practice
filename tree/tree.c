#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include "tree.h"

typedef struct node_s {
	void *data;
	void *child;
} tnode_t;

static void *tree_traverse_bfs(void *n_v, void *queue, int (*cb)(void *,
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
static void *tree_traverse_dfs(void *n_v, void *stack, int (*cb)(void *,
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

struct cb_s {
	int (*cb)(void *,void *);
	void *arg;
	void *ret;
};
int tree_traverse_bfs_level_cb(void *data, void *arg)
{
	struct cb_s *_cb = (struct cb_s *)arg;
	tnode_t *n = (tnode_t *)data;
	int ret = 0;
	ret = _cb->cb(n->data, _cb->arg);
	if (ret)
		_cb->ret = n;
	return ret;
}

void *tree_traverse_bfs_level(void *n_v, int (*cb)(void *,
							void *), void *arg)
{
	void *ret = NULL;
	tnode_t *n= (tnode_t *)n_v;
	if (!n)
		return ret;
	struct cb_s _cb;

	_cb.cb = cb;
	_cb.arg = arg;
	_cb.ret = NULL;

	list_traverse(n->child, HEAD, tree_traverse_bfs_level_cb, &_cb);
	return _cb.ret;
}

void *tree_traverse(void *n_v, ttype_t type, int (*cb)(void *,
							void *), void *arg) 
{
	void *ret = NULL;
	tnode_t *n= (tnode_t *)n_v;
	if (!n)
		return ret;

	if (type == BFS) {
		void *queue = list_init();
		list_add_node(queue, n, HEAD);
		ret = tree_traverse_bfs(n, queue, cb, arg);
		list_free(queue);
	}
	else if (type == DFS) {
		void *stack = list_init();
		list_add_node(stack, n, HEAD);
		ret = tree_traverse_dfs(n, stack, cb, arg);
		list_free(stack);
	}
	return ret;
}

void tree_free(void *n_v)
{

}

void *tree_add_node(void *pnode, void *data) 
{
	tnode_t *n = NULL, *parent = NULL;

	parent = (tnode_t *)pnode;

	n = calloc(1, sizeof(tnode_t));
	n->data = data;
	if (parent) {
		if (!parent->child)
			parent->child = list_init();
		list_add_node(parent->child, n, HEAD);
	}

	return n;
}


