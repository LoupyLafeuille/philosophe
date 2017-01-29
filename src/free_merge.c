/*
** free.c for malloc in /home/gaonac_l/rendu/PSU_2015_malloc
**
** Made by
** Login   <gaonac_l@epitech.net>
**
** Started on  Mon Jan 25 20:05:51 2016
** Last update Wed Feb 10 18:13:20 2016 
*/

#include <stdio.h>
#include <stdlib.h>
#include "libmalloc.h"

void				free(void *ptr)
{
  t_meta			*fblock;
  t_meta			*to_free;
  unsigned int			idx;

  if (ptr == NULL)
    return ;
  threading();
  to_free = ((t_meta*)ptr - 1);
  idx = ((unsigned int)to_free->size <= PAGE_SIZE) ?
    FIND_POW2(to_free->size) : 0;
  if ((fblock = list_pick(&g_used[idx], to_free)) != NULL)
    {
      if (idx == 0)
	recycling_block(fblock);
      else if (idx < FIND_POW2(PAGE_SIZE))
	merge_free(fblock, idx);
      else
	list_push_front(&g_free_tab[idx], fblock);
      unthreading();
      return ;
    }
  printf("Invalid free\n");
  unthreading();
  abort();
}
