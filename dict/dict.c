#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <tree.h>
#include <list.h>

#define MAX_WORD_SIZE 100

static int _compare_cb(void *data, int level, void *arg)
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
static int check_end_of_line(void *data, int level, void *arg)
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

#define MAX_SUGGESTIONS 10
static char sugg_buf[MAX_WORD_SIZE] = {0};
static int num_words = 0;
static int possible_words(void *data, int level, void *arg)
{
	char *c = (char *)data;

	if (*c == '\r')
	{
		printf ("%s ", sugg_buf);
		num_words++;
	}
	else {
		if (level)
			level -= 1;
		sugg_buf[level] = *c;
		sugg_buf[level+1] = '\0';
	}

	if (num_words >= MAX_SUGGESTIONS)
		return 1;
	return 0;
}

static void dict_input_word(void *root, char *buf)
{
	char *c = buf;
	void *n = root;
	while (*c != '\0')
	{
		n = tree_traverse_bfs_level(n, _compare_cb, c); 
		if (!n) {
			break;
		}
		c++;
	}
	if (!n)
		printf ("No suggestions!");
	else {
		num_words = 0;
		strncpy(sugg_buf, buf, strlen(buf)-1);
		tree_traverse(n, DFS, possible_words, NULL); 
	}

	return;
}

static void dict(void *root)
{
	system ("stty raw -echo\n");
	char buf[MAX_WORD_SIZE] = {0};
	int p = 0;

	while(1)
	{
		int c = getchar();

		if (c == 13) // enter
			break;
		else if (c == 127) // backspace
		{
			if (p)
				buf[--p] = '\0';
		}
		else
			buf[p++] = (char)c;

		printf ("\33[2K\r"); // clear and go to next line
		printf ("%s", buf);
		printf ("\r\n");
		printf ("\33[2K");
		if (p) 
			dict_input_word(root, buf);
		printf ("\033[1A"); // Go up one line
		printf ("\33[2K\r");
		printf ("%s", buf);
	}
	printf ("\r\n");
	printf ("\r\n");
	printf ("\33[2K\r");
	system ("stty cooked echo\n");
}

int main()
{
	FILE *fp = NULL;
	void *root = NULL;
	int tot = 0;

	fp = fopen("words-unsorted.txt", "r");
	root = populate_tree(fp);
	tot = find_max_words(root);

	printf ("Total number of words: %d\n", tot);

	fclose(fp);

	dict(root);
	tree_free(root);

	return 0;
}


