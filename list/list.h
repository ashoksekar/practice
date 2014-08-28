
typedef enum {
	STRAIGHT = 2,
	REVERSE = 3,
} type_t;
typedef enum {
	HEAD = 0,
	TAIL = 1,
} where_t;


extern void *list_init(void); 
extern void list_add_node(void *ctrl_v, void *data, type_t type);
extern void *list_remove_node(void *ctrl_v, type_t type);
extern void list_free(void *ctrl_v);
extern void list_traverse(void *ctrl_v, type_t type, int (*)(void *,
					    	 void *), void *arg);
extern void list_append(void *ctrl_v1, void *ctrl_v2, type_t type,
						where_t where);
