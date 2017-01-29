/*
** tools.c for malloc in /home/gaonac_l/rendu/PSU_2015_malloc
**
** Made by
** Login   <gaonac_l@epitech.net>
**
** Started on  Fri Jan 29 16:10:36 2016
** Last update Wed Feb 10 17:55:44 2016 
*/

#include "libmalloc.h"

size_t		next_power2(size_t nb)
{
  nb--;
  nb |= nb >> 1;
  nb |= nb >> 2;
  nb |= nb >> 4;
  nb |= nb >> 8;
  nb |= nb >> 16;
  nb |= nb >> 32;
  nb++;
  return (nb);
}

void		split_block(int idx)
{
  t_meta	*block;
  t_meta	*new;

  block = list_pop(&g_free_tab[idx]);
  block->size /= 2;
  new = (t_meta*)((long)block + block->size);
  new->size = block->size;
  new->next = NULL;
  list_push_front(&g_free_tab[idx - 1], block);
  list_push_front(&g_free_tab[idx - 1], new);
}

void		recycling_block(t_meta *block)
{
  t_meta	*cpy;
  int		idx;

  idx = FIND_POW2(PAGE_SIZE);
  if ((unsigned int)block->size > PAGE_SIZE)
    {
      cpy = (t_meta*)((long)block + PAGE_SIZE);
      cpy->size = block->size - PAGE_SIZE;
      cpy->next = NULL;
      block->next = NULL;
      block->size = PAGE_SIZE;
      list_push_front(&g_free_tab[idx], block);
      recycling_block(cpy);
    }
  else
    {
      list_push_front(&g_free_tab[idx], block);
      return ;
    }
}

void		merge_free(t_meta* ptr, int idx)
{
  t_meta	*prev;
  t_meta	*tmp;

  tmp = g_free_tab[idx].next;
  prev = &g_free_tab[idx];
  while (tmp)
    {
      if ((t_meta*)((long)ptr + ptr->size) == tmp)
	{
	  ptr->size *= 2;
	  prev->next = tmp->next;
	  ptr->next = NULL;
	  list_push_front(&g_free_tab[idx + 1], ptr);
	  return ;
	}
      prev = tmp;
      tmp = tmp->next;
    }
  list_push_front(&g_free_tab[idx], ptr);
}
