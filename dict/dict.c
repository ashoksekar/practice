#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <tree.h>
#include <list.h>

#define MAX_WORD_SIZE 100

static int _compare_cb(void *data, void *arg)
{
	char *c = (char *)data;
	char *cmp = (char *)arg;

	if (*c == *cmp)
		return 1;
	return 0;
}

static void *populate_tree(FILE *fp)
{
	char str[MAX_WORD_SIZE];
	void *root = NULL;
	char *data = calloc(1, sizeof(*data));
	int total = 0;

	root = tree_add_node( NULL, data);
	while (fgets(str, MAX_WORD_SIZE, fp) == str) {
		char *c = str;
		void *n = root, *parent = root;
		while (*c != '\0')
		{
			n = tree_traverse_bfs_level(parent, _compare_cb, c); 
			if (!n) {
				char *d = calloc(1, sizeof(*d));
				*d = *c;
				n = tree_add_node(parent, d);
				total++;
			}
			parent = n;
			c++;
		}
	}
	printf ("Total number of nodes added: %d\n", total);
	return root;
}

struct eol_s {
	int max;
	int current;
};
static int check_end_of_line(void *data, void *arg)
{
	char *c = (char *)data;
	struct eol_s *s = (struct eol_s *)arg;

	if (*c == '\n')
		s->current++;
	if (s->max && (s->current >= s->max))
		return 1;
	return 0;
}
static int find_max_words(void *n)
{
	struct eol_s arg = {0, 0};

	tree_traverse(n, BFS, check_end_of_line, &arg);

	return arg.current;
}

int main()
{
	FILE *fp = NULL;
	void *root = NULL;
	int tot = 0;

	fp = fopen("words.txt", "r");
	root = populate_tree(fp);
	tot = find_max_words(root);

	printf ("Total number of words: %d\n", tot);

	fclose(fp);
	return 0;
}


