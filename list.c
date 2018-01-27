#include "list.h"
#include <stdlib.h>
#include <stdio.h>

static Link *
new_link(void *data, Link *n)
{
  Link *p = malloc(sizeof(Link));
  if (p != NULL)
    {
      p->data = data;
      p->next = n;
      return p;
    }
  return NULL;
}

static void
delete_link(Link * link,
	    void (*delete_data)(void *))
{
  if (link->data != NULL)
    delete_data(link->data);
  free(link);
}
static void
free_list(Link * list)
{
  if (list == NULL)
    return;
  if (list->next != NULL)
    free_list(list->next);
  free(list);
  return;
}
/* wip the issue is the sorted half and unsorted half becomes unlinked */
void
list_sort(Link **list,
	  int (*compare)(void *, void *))
{
  if (*list == NULL)
    return;
  Link * new_list = NULL;
  Link ** lp = list;
  do
    {
      list_add_order(&new_list, (*lp)->data, compare);
      lp = &(*lp)->next;
    }
  while ((*lp)->next != NULL);
  Link * temp = *list;
  *list = new_list;
  free_list(temp);
  return;
}

int
list_add_order(Link **list, void *data,
		   int (*compare)(void *, void*))
{
  Link **lp = list;
  if (*lp != NULL)
    while ((*lp)->next != NULL)
      {
	if (compare((*lp)->data, data)>0)
	  break;
	lp = &(*lp)->next;
      }
  *lp = new_link(data,*lp);
  if (*lp != NULL)
    {
      return 0;
    }
  printf("no more memory\n");
  return 1;
}

int
list_add_index(Link **list, void *data, int index)
{
  Link **lp = list;
  if (*lp != NULL)
    while ((*lp)->next != NULL)
      {
	if (index == 0)
	  break;
	lp = &(*lp)->next;
	index--;
      }
  *lp = new_link(data,*lp);
  if (*lp != NULL)
    {
      return 0;
    }
  printf("no more memory\n");
  return 1;
}

int
list_add(Link **list, void *data)
{
  Link **lp = list;
  if (*lp != NULL)
    while ((*lp)->next != NULL)
      lp = &(*lp)->next;
  *lp = new_link(data,*lp);
  if (*lp != NULL)
    {
      return 0;
    }
  printf("no more memory\n");
  return 1;
}

int
list_delete_item(Link **list, void *data,
		 int (*compare)(void*,void*),
		 void (*delete_data)(void *))
{
  if (*list == NULL)
    return 0;
  Link **lp = list;
  for (; ; lp = &(*lp)->next)
    {
      if(compare((*lp)->data, data) == 0)
	{
	  Link * temp = *lp;
	  *lp = (*lp)->next;
	  delete_link(temp, delete_data);
	  return 0;
	}
      if ((*lp)->next != NULL)
	break;
    }
  return 1;
}

int
list_delete_index(Link **list, int index,
		  void (*delete_data)(void *))
{
  if (*list == NULL)
    return 0;
  Link **lp = list;
  for (; ; lp = &(*lp)->next, index--)
    {
      if(index == 0)
	{
	  Link * temp = *lp;
	  *lp = (*lp)->next;
	  delete_link(temp, delete_data);
	  return 0;
	}
      if ((*lp)->next != NULL)
	break;
    }
  return 1;
}

int
list_delete_all_item(Link **list, void *data,
		 int (*compare)(void*,void*),
		 void (*delete_data)(void *))
{
  if (*list == NULL)
    return 0;
  Link **lp = list;
  for (; ; lp = &(*lp)->next)
    {
      if(compare((*lp)->data, data) == 0)
	{
	  Link * temp = *lp;
	  *lp = (*lp)->next;
	  delete_link(temp, delete_data);
	}
      if ((*lp)->next != NULL)
	break;
    }
  return 0;
}

int
list_remove_index(Link **list, int index)
{
  if (*list == NULL)
    return 0;
  Link **lp = list;
  for (; ; lp = &(*lp)->next, index--)
    {
      if(index == 0)
	{
	  Link * temp = *lp;
	  *lp = (*lp)->next;
	  free(temp);
	  return 0;
	}
      if ((*lp)->next != NULL)
	break;
    }
  return 0;
}
int
list_remove_item(Link **list, void *data,
		 int (*compare)(void *, void*))
{
  if (*list == NULL)
    return 0;
  Link **lp = list;
  for (; ; lp = &(*lp)->next)
    {
      if(compare((*lp)->data, data) == 0)
	{
	  Link * temp = *lp;
	  *lp = (*lp)->next;
	  free(temp);
	  return 0;
	}
      if ((*lp)->next != NULL)
	break;
    }
  return 0;
}
int
list_append(Link ** list_a, Link * list_b)
{
  Link **lp = list;
  if (*lp != NULL)
    while ((*lp)->next != NULL)
      lp = &(*lp)->next;
  *lp = list_b;
  return 0;
}
Link *
list_from_array(void **array)
{
  Link * list = NULL;
  Link ** lp = &list;
  int i;
  for (i = 0; array[i]; i++)
    {
      *lp = new_link(array[i], NULL);
      lp = &(*lp)->next;
    }
  return list;
}
int
list_add_array(Link ** list, void **array)
{
  list_append(list, list_from_array(array));
  return 0;
}
Link *
list_from_array_length(void ** array, int length)
{
  Link * list = NULL;
  Link ** lp = &list;
  int i;
  for (i = 0; i < length; i++)
    {
      *lp = new_link(array[i], NULL);
      lp = &(*lp)->next;
    }
  return list;
}
int
list_add_array_length(Link **list, void ** array, int length)
{
  list_append(list, list_from_array_length(array, length));
  return 0;
}
Link *
list_get(Link * list, void * data,
	 int (*commpare)(void *, void *))
{
  if (list == NULL)
    return NULL;
  Link **lp;
  for (lp = list; (*lp)->next != NULL; lp = &(*lp)->next)
    {
      if(compare((*lp)->data, data) == 0)
	{
	  return *lp;
	}
    }
  if(compare((*lp)->data, data) == 0)
    {
      return *lp;
    }
  return NULL;
}
