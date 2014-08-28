
typedef enum traverse_type {
	BFS = 0,
	DFS = 1,
} ttype_t;

extern void tree_add_node(void *ctrl_v, void *pdata, void *data);
extern void tree_free(void *ctrl_v);
extern void *tree_traverse(void *ctrl_v, ttype_t type, int (*cb)(void *,
							 void *), void *arg) ;
extern void *tree_init(void);
