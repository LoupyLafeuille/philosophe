/*
** link_list.c for malloc in /home/gaonac_l/rendu/PSU_2015_malloc
**
** Made by
** Login   <gaonac_l@epitech.net>
**
** Started on  Thu Jan 28 19:10:07 2016
** Last update Wed Feb 10 17:53:27 2016 
*/

#include <math.h>
#include "libmalloc.h"

static t_meta	*init_ptrs(t_meta *ptr1, t_meta *val1,
			   t_meta *ptr2, t_meta *val2)
{
  ptr1->next = val1;
  ptr2->next = val2;
  return (ptr2);
}

t_meta		*list_pick(t_meta *list, t_meta *ptr)
{
  t_meta	*tmp;
  t_meta	*prev;

  tmp = list->next;
  prev = list;
  while (tmp)
    {
      if (tmp == ptr && tmp->next == NULL)
	return (init_ptrs(prev, NULL, tmp, NULL));
      else if (tmp == ptr && tmp == list->next)
	return (init_ptrs(list, tmp->next, tmp, NULL));
      else if (tmp == ptr && prev->next == tmp)
	return (init_ptrs(prev, tmp->next, tmp, NULL));
      prev = tmp;
      tmp = tmp->next;
    }
  return (NULL);
}

t_meta		*list_pick_size(t_meta *list, int size)
{
  t_meta	*tmp;
  t_meta	*prev;

  tmp = list->next;
  prev = list;
  while (tmp)
    {
      if (tmp->size >= size && tmp->next == NULL)
	return (init_ptrs(prev, NULL, tmp, NULL));
      else if (tmp->size >= size && tmp == list->next)
	return (init_ptrs(list, tmp->next, tmp, NULL));
      else if (tmp->size >= size && prev->next == tmp)
	return (init_ptrs(prev, tmp->next, tmp, NULL));
      prev = tmp;
      tmp = tmp->next;
    }
  return (NULL);
}

int		list_push_front(t_meta *list, t_meta *ptr)
{
  ptr->next = list->next;
  list->next = ptr;
  return (0);
}

t_meta		*list_pop(t_meta *list)
{
  t_meta	*ptr;

  ptr = NULL;
  if (list->next)
    {
      ptr = list->next;
      list->next = list->next->next;
    }
  return (ptr);
}
