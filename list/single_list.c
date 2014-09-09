#include <stdio.h>
#include <stdlib.h>

typedef struct node_s {
	int data;
	struct node_s *link;
}node_t;

node_t *add_node(node_t *head, int data)
{
	node_t *n = calloc(1, sizeof(node_t));

	n->link = head;
	n->data = data;
	return n;
}

node_t *reverse_list(node_t *q)
{
	node_t *p = NULL, *r = NULL;

	while (q)
	{
		r = q->link;
		q->link = p;
		p = q;
		q = r;
	}
	return p;
}

void print_list(node_t *n)
{
	while (n)
	{
		printf ("%d ", n->data);
		n = n->link;
	}
	printf ("\n");
}
int main()
{
	int c;
	node_t *head = NULL;

	while (1)
	{
		printf ("1. Add node\n");
		printf ("2. Print list\n");
		printf ("3. Reverse list\n");
		printf ("4. Exit\n");
		printf ("Enter your option: ");
		scanf ("%d", &c);
		switch(c) {
			case 1:
				{
					int data;
					printf ("Enter data: ");
					scanf ("%d", &data);
					head = add_node(head, data);
				}
				break;
			case 2:
				{
					print_list(head);
				}
				break;
			case 3:
				head = reverse_list(head);
				break;
			case 4:
				exit(0);
				break;
			default:
				printf ("Invalid option\n");
				break;
		}
	}
	return 0;
}
