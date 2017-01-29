/*
** show_alloc_mem.c for malloc in /home/gaonac_l/rendu/PSU_2015_malloc
** 
** Made by 
** Login   <gaonac_l@epitech.net>
** 
** Started on  Tue Jan 26 11:54:31 2016 
** Last update Wed Feb 10 17:08:20 2016 
*/

#include <stdio.h>
#include "libmalloc.h"

void		show_alloc_mem()
{
  t_meta	*block;
  unsigned int	i;
  unsigned int	size;

  size = FIND_POW2(PAGE_SIZE) + 1;
  i = 0;
  printf("%p\n", sbrk(0));
  while (i < size)
    {
      block = g_used[i].next;
      while (block)
	{
	  printf("%p - %lx : %u octets\n"
		 , block + 1, ((long)(block + 1)) + block->size, block->size);
	  block = block->next;
	}
      ++i;
    }
}
