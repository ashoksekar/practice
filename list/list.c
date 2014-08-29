#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct node_s;

typedef struct ctrl_s {
	struct node_s *head;
	struct node_s *tail;
}lctrl_t;
typedef struct node_s {
	void *data;
	struct node_s *prev;
	struct node_s *next;
}lnode_t;

void *list_init(void) {
	return calloc(1,sizeof(lctrl_t));
}

static int __list_append_start(void *n, void *arg)
{
	lctrl_t *c = (lctrl_t *)arg;
	list_add_node(c, n, HEAD);
	return 0;
}

static int __list_append_end(void *n, void *arg)
{
	lctrl_t *c = (lctrl_t *)arg;
	list_add_node(c, n, TAIL);
	return 0;
}

void list_append(void *ctrl_v1, void *ctrl_v2, type_t type, where_t where)
{
	lctrl_t *ctrl1 = (lctrl_t *)ctrl_v1;
	lctrl_t *ctrl2 = (lctrl_t *)ctrl_v2;

	if (where == HEAD) {
		if (type == STRAIGHT)
			list_traverse(ctrl2, TAIL, __list_append_start, ctrl1);
		else if (type == REVERSE)
			list_traverse(ctrl2, HEAD, __list_append_start, ctrl1);
	}
	else if (where == TAIL) {
		if (type == STRAIGHT)
			list_traverse(ctrl2, HEAD, __list_append_end, ctrl1);
		else if (type == REVERSE)
			list_traverse(ctrl2, TAIL, __list_append_end, ctrl1);
	}
	return;
}
void list_traverse(void *ctrl_v, type_t type, int (*cb)(void *, void *),
				   void *arg) 
{
	lctrl_t *ctrl = (lctrl_t *)ctrl_v;
	lnode_t *n;

	if (!ctrl)
		return;
	if (type == HEAD) {
		n = ctrl->head;
		while (n) {
			if (cb(n->data, arg))
				break;
			n = n->next;
		}
	} else if (type == TAIL) {
		n = ctrl->tail;
		while (n) {
			if (cb(n->data, arg))
				break;
			n = n->prev;
		}
	}
	return;
}

void list_add_node(void *ctrl_v, void *data, type_t type)
{
	lctrl_t *ctrl = (lctrl_t *)ctrl_v;
	lnode_t *n = NULL;

	if (!data || !ctrl)
		return;
	n = calloc(1, sizeof(lnode_t));
	n->data = data;
	if (!ctrl->head) {
		ctrl->head = n;
	} else if (type == HEAD) {
		n->next = ctrl->head;
		ctrl->head->prev = n;
		ctrl->head = n;
	}
	if (!ctrl->tail) {
		ctrl->tail = n;
	} else if (type == TAIL) {
		n->prev = ctrl->tail;
		ctrl->tail->next = n;
		ctrl->tail = n;
	}
}

void *list_remove_node(void *ctrl_v, type_t type)
{
	lctrl_t *ctrl = (lctrl_t *)ctrl_v;
	lnode_t *n;
	void *data = NULL;

	if (type == HEAD) {
		if (ctrl->head) {
			n = ctrl->head;
			ctrl->head = ctrl->head->next;
			if (ctrl->head)
				ctrl->head->prev = NULL;
			else
				ctrl->tail = NULL;
			data = n->data;
			free(n);
		} 
	} else if (type == TAIL) {
		if (ctrl->tail) {
			n = ctrl->tail;
			ctrl->tail = ctrl->tail->prev;
			if (ctrl->tail)
				ctrl->tail->next = NULL;
			else 
				ctrl->head = NULL;
			data = n->data;
			free(n);
		}
	}
	return data;
}

void list_free(void *ctrl_v) 
{
	lctrl_t *ctrl = (lctrl_t *)ctrl_v;
	lnode_t *n = ctrl->head, *t = NULL;

	while(n) {
		t = n;
		n = n->next;
		free(t);
	}

	free(ctrl);
	return;
}

