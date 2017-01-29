/*
** malloc.c for malloc in /home/gaonac_l/rendu/PSU_2015_malloc
**
** Made by
** Login   <gaonac_l@epitech.net>
**
** Started on  Mon Jan 25 16:38:13 2016
** Last update Wed Feb 10 17:55:25 2016 
*/

#include <string.h>
#include "libmalloc.h"

t_meta			*g_free_tab = NULL;
t_meta			*g_used = NULL;

static int		setup_memory()
{
  unsigned int		i;
  unsigned int		size;
  t_meta		*page;

  if ((g_free_tab = sbrk(2 * PAGE_SIZE)) == (void*) - 1)
    return (1);
  size = FIND_POW2(PAGE_SIZE) + 1;
  i = 0;
  while (i < size)
    {
      g_free_tab[i].size = 0;
      g_free_tab[i++].next = NULL;
    }
  g_used = &g_free_tab[i];
  memcpy(g_used, g_free_tab, size * META_SIZE);
  page = (t_meta*)((long)g_free_tab + PAGE_SIZE);
  page->next = NULL;
  page->size = PAGE_SIZE;
  g_free_tab[size - 1].next = page;
  return (0);
}

static void		*extend_memory(size_t size, t_meta *list)
{
  t_meta		*block;

  if ((block = list_pick_size(&g_free_tab[0], size)) != NULL)
    {
      list_push_front(&g_used[0], block);
      return (block + 1);
    }
  if ((block = sbrk(size)) == (void*) - 1)
    return (NULL);
  block->size = size;
  block->next = NULL;
  list_push_front(list, block);
  return (block + 1);
}

static void		*search_block(unsigned int idx, unsigned int org)
{
  t_meta		*block;

  if (idx == FIND_POW2(PAGE_SIZE) && g_free_tab[idx].next == NULL)
    {
      if (extend_memory(PAGE_SIZE, &g_free_tab[idx]) == NULL)
	return (NULL);
      return (search_block(idx, org));
    }
  else if (g_free_tab[idx].next != NULL)
    {
      if (org < idx)
	{
	  split_block(idx);
	  return (search_block(idx - 1, org));
	}
      else if (org == idx)
	{
	  block = list_pop(&g_free_tab[idx]);
	  list_push_front(&g_used[idx], block);
	  return (block + 1);
	}
    }
  else if (g_free_tab[idx].next == NULL)
    return (search_block(idx + 1, org));
  return (NULL);
}

void		*unsafe_malloc(size_t size)
{
  if (g_free_tab == NULL)
    {
      if (setup_memory())
	return (NULL);
    }
  size = next_power2(size + META_SIZE);
  if (size > PAGE_SIZE)
    return (extend_memory(size, &g_used[0]));
  else
    {
      size = FIND_POW2(size);
      return (search_block(size, size));
    }
}

void		*malloc(size_t size)
{
  void		*ptr;

  threading();
  ptr = unsafe_malloc(size);
  unthreading();
  return (ptr);
}
