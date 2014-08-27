#include <stdio.h>
#include "list.h"

typedef struct ctrl_s {
	node_t *head;
	node_t *tail;
}ctrl_t;
typedef struct node_s {
	void *data;
	struct node_s *prev;
	struct node_s *next;
}node_t;

void *init_list(void) {
	return calloc(1,sizeof(ctrl_t));
}

void traverse_list(void *ctrl_v, type_t type, (int (*cb)(void *, void *)),
				   void *arg) 
{
	ctrl_t *ctrl = (ctrl_t *)ctrl_v;
	node_t *n;

	if (type == START) {
		n = ctrl->head;
		while (n) {
			if (cb(n->data))
				break;
			n = n->next;
		}
	} else if (type == END) {
		n = ctrl->tail;
		while (n) {
			if (cb(arg, n->data))
				break;
			n = n->prev;
		}
	}
	return;
}

void add_node(void *ctrl_v, void *data, type_t type)
{
	ctrl_t *ctrl = (ctrl_t *)ctrl_v;
	node_t *n = calloc(1, sizeof(node_t));
	n->data = data;
	if (!ctrl->head) {
		ctrl->head = n;
	} else if (type == START) {
		n->next = ctrl->head;
		ctrl->head->prev = n;
		ctrl->head = n;
	}
	if (!ctrl->tail) {
		ctrl->tail = n;
	} else if (type == END) {
		n->prev = ctrl->tail;
		ctrl->tail->next = n;
		ctrl->tail = n;
	}
}

void *remove_node(void *ctrl_v, type_t type)
{
	ctrl_t *ctrl = (ctrl_t *)ctrl_v;
	node_t *n;
	void *data = NULL;

	if (type == START) {
		if (ctrl->head) {
			n = ctrl->head;
			ctrl->head = ctrl->head->next;
			ctrl->head->prev = NULL;
			data = n->data;
			free(n);
		} 
	} else if (type == END) {
		if (ctrl->tail) {
			n = ctrl->tail;
			ctrl->tail = ctrl->tail->prev;
			ctrl->tail->next = NULL;
			data = n->data;
			free(n);
		}
	}
	return data;
}

void free_list(void *ctrl_v) 
{
	ctrl_t *ctrl = (ctrl_t *)ctrl_v;
	node_t *n = ctrl->head;

	while(n) {
		t = n;
		n = n->next;
		free(t);
	}

	free(ctrl);
	return;
}

