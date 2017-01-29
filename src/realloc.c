/*
** realloc.c for malloc in /home/gaonac_l/rendu/mallocv2
**
** Made by
** Login   <gaonac_l@epitech.net>
**
** Started on  Wed Jan 27 11:54:28 2016
** Last update Thu Feb 11 21:00:14 2016 
*/

#include "libmalloc.h"

void				*realloc(void *old, size_t size)
{
  char				*buff;
  t_meta			*new;
  unsigned int			old_size;
  unsigned			i;

  if (old == NULL)
    return (malloc(size));
  else if (size == 0)
    {
      free(old);
      return (malloc(size));
    }
  if ((new = malloc(size)) == NULL)
    return (NULL);
  buff = (char*)new;
  old_size = ((t_meta*)old - 1)->size - META_SIZE;
  i = 0;
  while (i < old_size && i < size)
    {
      buff[i] = ((char*)old)[i];
      i++;
    }
  free(old);
  return (buff);
}
