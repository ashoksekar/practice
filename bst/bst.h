
extern void *add_node(void *root, void *data);
extern void *traverse_tree(void *n, int (*cb)(void *, void *), void *arg);
extern int height_tree(void *n);
