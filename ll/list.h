
typedef enum {
	START = 0,
	END = 1,
} type_t;


extern void *init_list(void); 
extern void add_node(void *ctrl_v, void *data, type_t type);
extern void *remove_node(void *ctrl_v, type_t type);
extern void free_list(void *ctrl_v);
extern void traverse_list(void *ctrl_v, type_t type, (int (*cb)(void *,
																void *)));
