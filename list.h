#ifndef _LIST_H_
#define _LIST_H_
typedef struct Link
{
  void *data;
  struct Link *next;
}Link;
/* sort the list */
void
list_sort(Link **list,
	  int (*compare)(void *, void *));

/* link will not make a copy */
int
list_add_order(Link **list, void *data,
		   int (*compare)(void *, void*));
int
list_add_index(Link **list, void *data, int index);
/* link to the end */
int
list_add(Link **list, void *data);

/* delete will free the space */
int
list_delete_item(Link **list, void *data,
		 int (*compare)(void *, void*),
		 void (*delete_data)(void *));
int
list_delete_index(Link **list, int index,
		     void (*delete_data)(void *));
/* delete all that mach with data */
int
list_delete_all_item(Link **list, void *data,
		     int (*compare)(void *, void*),
		     void (*delete_data)(void *));

/* will remove from chain */
int
list_remove_index(Link **list, int index);
int
list_remove_item(Link **list, void *data,
		 int (*compare)(void *, void*));
/* append list b to a */
int
list_append(Link **list_a, Link * list_b);

/* add null terminated array to list */
int
list_add_array(Link ** list, void **array);
/* add  length of array to list*/
int
list_add_array_length(Link ** list, void **array, int length);
Link *
list_get(Link * list, void * data,
	 int (*compare)(void *, void*));
int
list_push(Link ** list, void * data);
void *
list_pull(Link ** list);
#endif
