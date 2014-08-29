
typedef enum traverse_type {
	BFS = 0,
	DFS = 1,
} ttype_t;

extern void *tree_add_node(void *n_v, void *pdata, void *data);
extern void tree_free(void *n_v);
extern void *tree_traverse(void *n_v, ttype_t type, int (*cb)(void *,
							 void *), void *arg) ;
